import { db, realtimeDB } from './firestore.firebase';
import { exec } from 'child_process';
const glob = require('glob');
const path = require('path');
const fs = require('fs');

const getContent = async (file) => {
	return new Promise((resolve, reject) => {
		fs.readFile(file, { encoding: 'utf8' }, (err, data) => {
			if (err) reject(err);

			resolve(data)
		})
	})
}

const populate = async (collection) => {
	const filesPath = './resources/champs/*.s';

	db.collection('users').where('name', '==', 'default').get()
	.then(user => {
		if (user.size === 0)
		if (user.size > 1)
			return console.error('too many defaults');
		user.forEach(u => {
			console.log(`Populating collection`);
			glob(filesPath, {}, (err, files) => {
				if (err) throw new Error(`Error: ${err.message}`);

				if (files && files.length > 0) {
					for (const file of files) {
						getContent(file)
						.then(content => {
							collection.add({
								basename: path.basename(file, '.s'),
								path: file,
								content,
								ownerId: u.id,
								timestamp: Date.now()
							});
							console.log(`Data added: ${file}`);
						}).catch(err => console.error(err));
					}
				}
				else
					console.error(`Error: no file found under ${filesPath}`);
			});
		});
	});
}

const deleteCollection = async (collection, snapshot) => {
	console.log(`Deleting collection`);
	snapshot.forEach(snap => {
		console.log(`deleted ${snap.id}`);
		collection.doc(snap.id).delete();
	});
}

export const populateIfZero = async () => {
	const champs = db.collection('champs');
	const challenges = db.collection('challenges');

	champs.get()
	.then(snapshot => {
		if (snapshot.size === 0)
			populate(champs);
		else {
			deleteCollection(champs, snapshot);
			populate(champs);
		}
	}).catch(err => console.error(err));

	challenges.get()
	.then(snapshot => snapshot.forEach(snap => challenges.doc(snap.id).delete()))
	realtimeDB.ref('challenges').remove();

	exec('killall corewar');
};
