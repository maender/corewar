import { db, realtimeDB } from '../firebase/firestore.firebase';
import { NOT_FOUND } from '../../constants/errors.constants';

const challenges = async (root, {id}) => {
	const ref = realtimeDB.ref(`challenges/${id}`);
	console.log(`Getting all user challenges with userid: ${id}`);
	return new Promise((resolve, reject) => {
		ref.once('value').then(data => {
			console.log(data.val());
			const arr = [];
			data.forEach(challenge => {
				arr.push({
					id: challenge.key,
					stat: challenge.val().stat,
					timestamp: challenge.val().timestamp,
					total: challenge.val().totalOpponent,
					err: null,
					errCode: null
				});
			});
			console.log(arr);
			resolve(arr);
		})
	});
}

export default challenges;