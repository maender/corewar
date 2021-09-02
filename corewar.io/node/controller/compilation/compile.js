import { db } from '../firebase/firestore.firebase';
import { exec } from 'child_process';
import { NOT_FOUND, ERR } from '../../constants/errors.constants';

const glob = require('glob');

const compile = async (root, { id, userid }) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('champs');

		collection.doc(id).get()
		.then(doc => {
			if (doc.empty)
				return resolve(NOT_FOUND);
			else if (doc.data().ownerId !== userid)
				return resolve(NOT_FOUND);
			else if (doc.data().path) {
				glob(doc.data().path, {}, (err, data) => {
					if (err) resolve(ERR(err));
					if (data.length > 0) {
						const exec_path = `./resources/corewar/asm "${data[0]}"`;

						console.log(exec_path);
						exec(exec_path, (err, stdout, stderr) => {
							if (err) resolve({
								err: err.message,
								errCode: err.code,
								stdout,
								stderr
							});

							console.log('stdout: ', stdout);
							console.log('stderr: ', stderr);
							resolve({
								stdout: stdout,
								stderr: stderr
							});
						});
					}
				});
			}
		});
	});
}

export default compile;
