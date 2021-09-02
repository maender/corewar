import { db } from '../firebase/firestore.firebase';
import { NOT_FOUND } from '../../constants/errors.constants';

const userById = async (root, { id }) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('users');

		collection.doc(id).get()
		.then(doc => {
			console.log(id);
			if (doc.empty)
				resolve(NOT_FOUND);
			resolve({
				id,
				email: doc.data().email,
				avatar: doc.data().avatar,
				name: doc.data().name
			});
		});
	});
}

export default userById;
