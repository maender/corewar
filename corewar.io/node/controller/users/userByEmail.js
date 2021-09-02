import { db } from '../firebase/firestore.firebase';
import { NOT_FOUND } from '../../constants/errors.constants';

import { QUERY_ERROR } from '../../constants/errors.constants';

const userByEmail = async (root, { email }) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('users');

		collection.where('email', '==', email).get()
		.then(doc => {
			if (doc.empty)
				resolve(NOT_FOUND)
			if (doc.size > 1)
				resolve(QUERY_ERROR)
			doc.forEach(d => {
				resolve({
					id: d.id,
					name: d.data().name,
					avatar: d.data().avatar,
					email: d.data().email
				});
			});
		});
	});
}

export default userByEmail;
