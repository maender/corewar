import { db } from '../firebase/firestore.firebase';

const isChampUnique = async (root, { name }) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('champs');

		collection.where('basename', '==', name).get()
		.then(doc => resolve({result: doc.empty}));
	});
}

export default isChampUnique;
