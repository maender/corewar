import { db } from '../firebase/firestore.firebase';
import { NOT_FOUND, ERR } from '../../constants/errors.constants';

const champ = async (root, {basename}) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('champs');

		collection.where('basename', '==', basename).get()
			.then(doc => {
				if (doc.empty)
					resolve(NOT_FOUND);
				doc.forEach(d => {
					console.log(d.id, d.data().basename)
					resolve({
					id: d.id,
						basename: d.data().basename,
						path: d.data().path,
						ownerId: d.data().ownerId,
						timestamp: d.data().timestamp,
						lastUpdate: d.data().lastUpdate,
						content: d.data().content
					});
				})
				resolve({ok: 'ok'});
			}).catch(err => resolve(ERR(err)));
	})
}

export default champ;
