import { db } from '../firebase/firestore.firebase';
import { exec } from 'child_process';

const fs = require('fs');

const emmergencyExit = (exe, cor1, cor2) => {
	const emmergencyCmd = `ps -a | grep "${exe} ${cor1} ${cor2}" | sed 's/ .*//'`;
	const killProcess = 'kill `' + emmergencyCmd + '`';

	console.log(`Fight too long, running emmergency exit command:\n${killProcess}`);
	exec(killProcess, (err, stdout, stderr) => console.log(`\nStopped battle between ${cor1} and ${cor2}; err: ${err}, stdout: ${stdout}, stderr: ${stderr}`));
}

const executeFight = async (cor1, cor2, c1, c2, resolve, reject) => {
	const exe = `./resources/corewar/corewar`
	const name1 = c1.data().basename;
	const name2 = c2.data().basename;
	const id1 = c1.id;
	const id2 = c2.id;
	const cmd = `${exe} "${cor1}" "${cor2}"`;

	const timer = setTimeout(() => {
		emmergencyExit(exe, cor1, cor2);
		resolve({err: 'TIMEOUT', errCode: 408});
		return ;
	}, 1000 * 30);
	exec(cmd, (err, stdout, stderr) => {
		if (err) resolve({err: err.message, errCode: err.errno});

		clearTimeout(timer);
		if (stdout) {
			const lines = stdout.split('\n');

			for (let i = 0; i < lines.length; i++) {
				if (lines[i].search("won!") !== -1) {
					const playerNum = parseInt(lines[i].substring(7, lines[i].length));
					if (playerNum === 1 || playerNum === 2) {
						resolve({
							id: playerNum === 1 ? id1 : id2,
							challenger: name1,
							opponent: name2,
							winner: playerNum === 1 ? name1 : name2,
							stdout
						});
					}
					else {
						resolve({
							err: 'cannot get a winner',
							challenger: name1,
							opponent: name2,
							winner: 'Nobody',
							stdout
						});
					}
				}
			}
		} else {
			resolve({
				err: stderr,
				errCode: 500
			});
		}
	});

}

const checkCorFiles = async (c1, c2, resolve, reject) => {
	const cor1 = `${c1.data().path.substring(0, c1.data().path.length - 2)}.cor`;
	const cor2 = `${c2.data().path.substring(0, c2.data().path.length - 2)}.cor`;

	fs.exists(cor1, e1 => {
		fs.exists(cor2, e2 => {
			if (e1 && e2)
				executeFight(cor1, cor2, c1, c2, resolve, reject);
			else
				resolve({err: `Could not locate all champs, c1: ${e1}, c2: ${e2}, cor1: ${cor1}, cor2: ${cor2}`, errCode: 404});
		})
	});
}

const fight = async (root, { champ1, champ2 }) => {
	return new Promise((resolve, reject) => {
		const collection = db.collection('champs');

		collection.where('basename', '==', champ1).get()
		.then(ch1 => {
			if (ch1.empty)
				resolve({err: `${champ1} Not found`, errCode: 404});
			ch1.forEach(c1 => {
				collection.where('basename', '==', champ2).get()
				.then(ch2 => {
					if (ch2.empty)
						resolve({err: `${champ2} not found`, errCode: 404});

					ch2.forEach(c2 => checkCorFiles(c1, c2, resolve, reject));
				});
			});
		}).catch(err => {
			console.error(`Got an error while fighting`, err);
			resolve({err: err.message, errCode: err.code});
		});
	});
}

export default fight;
