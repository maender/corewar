import { db, realtimeDB } from '../firebase/firestore.firebase';
import champs from '../champions/champs';
import fight from './fight';

const testChallenge = [
	{
		id: "someId",
		challenger: "challenger name",
		opponent: "opponent name",
		winner: "winner name",
		stdout: "stdout",
		err: null,
		errCode: null
	}
];

const loopChampsRealtime = async (champs, challenger, userid, root, key, ref)  => {
	const challengeRef = ref.child(key);

	challengeRef.update({pending: true, totalOpponent: champs.length});
	console.log(champs.length);
	for (let i = 0; i < champs.length; i++) {
		if (champs[i] && champs[i].basename !== challenger) {
			const basename = champs[i].basename;

			console.log(`Start fight nº${i + 1}: ${challenger} VS ${basename}`);
			if (!isNaN(champs.length))
				challengeRef.update({totalOpponent: champs.length});
			await fight(root, {champ1: challenger, champ2: basename})
			.then(data => {
				if (data.err)
					if (!isNaN(low.val().totalOpponent - 1) && low.val().totalOpponent)
						return ref.once('value').then((low) => challengeRef.update({totalOpponent: low.val().totalOpponent - 1}));

				challengeRef.once('value').then(snap => {
					let j = 0;
					const arr = snap.val().result ? snap.val().result : [];

					if (arr.length > 0) {
						arr.forEach(a => {
							if (a.challenger === a.winner)
								j++;
						});
						const stat = j / arr.length * 100;

						arr.push(data);
						console.dir(arr);
						challengeRef.update({stat, result: arr})
						.catch(err => console.error(`ERROR: ${err.message}`));
					}
					else {
						const stat = (data.winner === data.challenger) * 100;

						arr.push(data);
						console.dir(arr);
						challengeRef.update({stat, result: arr})
						.catch(err => console.error(`ERROR: ${err.message}`));
					}
				}).catch(err => console.error(`ERROR: ${err.message}`));
			}).catch(err => console.error(`ERROR: ${err.message}`));
		}
		else
			console.error(`We will not start a fight against himself`);
	}
	challengeRef.update({pending: false, currOpponent: null});
}

const challengeEverybody = async (root, { challenger, userid }) => {
	const collection = 'challenges';
	const challengeRef = realtimeDB.ref(`${collection}/${userid}`);
	console.log('Challenge in progress...', challenger, userid);

	return new Promise((resolve, reject) => {
		const key = challengeRef.push({
			timestamp: Date.now(),
			userid,
			result: []
		}).key;
		console.log(`new key: ${key}`);
		challengeRef.child(key).once('value').then(data => {
			console.log(data.val());
			resolve({id: key, err: null, errCode: null});
			champs().then(champs => loopChampsRealtime(champs, challenger, userid, root, key, challengeRef));
		});
	});
};

export default challengeEverybody;
