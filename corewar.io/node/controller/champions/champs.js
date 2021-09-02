import { db } from '../firebase/firestore.firebase';
import { NOT_FOUND, ERR } from '../../constants/errors.constants';

const champs = async () => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('champs');
		const arr = [];

		collection.orderBy('basename').get()
		.then((doc) => {
			if (doc.empty)
				resolve(NOT_FOUND)
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
			resolve(arr);
		})
		.catch(err => {
			resolve([ERR(err)]);
		});
	});
}

export default champs;
