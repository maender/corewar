import { db } from '../firebase/firestore.firebase';

const fs = require('fs');

const saveChampion = async (root, { name, userid, content }) => {
	console.log("saving");
	return new Promise((resolve, reject) => {
		// const collection = db.collection('champs');
		const path = `./resources/user_champions/${userid}/`;

		fs.mkdir(path, {recursive: true}, (err) => {
			if (!err || (err && err.code === 'EEXIST')) {
				fs.writeFile(`${path}${name}.s`, content, err => {
					if (err) throw err;
					console.log('data has been saved');
					const collection = db.collection('champs');

					const newDoc = {
						path: `${path}${name}.s`,
						basename: `${name}`,
						content,
						ownerId: userid,
						timestamp: Date.now(),
						lastUpdate: Date.now()
					};
					collection.add(newDoc)
					.then((data) => {
						resolve({
							id: data.id,
							basename: newDoc.basename,
							content: newDoc.content,
							timestamp: newDoc.timestamp,
							lastUpdate: newDoc.lastUpdate,
							ownerId: newDoc.ownerId
						});
					});
				});
			}
			else {
				console.log(err);
				resolve({err: err.message, errCode: err.errno});
			}
		});
	})
}


export default saveChampion;
