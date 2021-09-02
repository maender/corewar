import { db } from '../firebase/firestore.firebase';
import { NOT_FOUND, ERR } from '../../constants/errors.constants';

const userChamps = async (root, { id }) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('champs');
		const arr = [];

		collection.where('ownerId', '==', id).get()
		.then((doc) => {
			if (doc.empty)
				resolve([NOT_FOUND]);
			doc.forEach(d => {
				arr.push({
					id: d.id,
					basename: d.data().basename,
					path: d.data().path,
					ownerId: d.data().ownerId,
					timestamp: d.data().timestamp,
					lastUpdate: d.data().lastUpdate,
					content: d.data().content
				});
			});
			const sorted = arr.sort((a, b) => {
				if (a.basename.toUpperCase() < b.basename.toUpperCase())
					return -1;
				if (b.basename.toUpperCase() < a.basename.toUpperCase())
					return 1;
				return 0;
			})
			resolve(sorted);
		})
		.catch(err => {
			console.error(err);
			resolve([ERR(err)]);
		});
	});
}

export default userChamps;
