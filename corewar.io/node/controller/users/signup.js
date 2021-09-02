import { db } from '../firebase/firestore.firebase';

const signup = async (root, { userid, name, email }) => {
	return new Promise((resolve, reject) => {
		db.collection('users').doc(userid).set({
			name,
			email
		}).then(() => resolve({result: true}))
		.catch((err) => resolve({result: false, err: err.message, errCode: err.code}));
	});
}

export default signup;