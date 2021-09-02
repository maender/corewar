import { db } from '../firebase/firestore.firebase';

const fs = require('fs');

const updateChampion = async (root, { name, userid, content }) => {
	console.log('updating champion');
	return new Promise((resolve, reject) => {
		const path = `./resources/user_champions/${userid}/${name}.s`;

		const collection = db.collection('champs');

		collection.where('basename', '==', name).get()
		.then(doc => {
			if (doc.empty)
				resolve({err: "Not found", errCode: 404});
			doc.forEach(d => {
				console.log("in foreach", d.data().path);
				fs.writeFile(`${d.data().path}`, content, (err) => {
					if (err) throw err;

					collection.doc(d.id).update({
						content,
						lastUpdate: Date.now()
					}).then(done => {
						console.log(done);
						resolve({id: d.id, basename: name});
					});
				});
			});
		});
	});
}

export default updateChampion;
