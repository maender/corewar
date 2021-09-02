import * as firebase from 'firebase/app';
import { fetchGraph } from './GraphTools';

const getUser = async () => {
	const userId = await firebase.auth().currentUser.uid
	
	return new Promise((resolve, reject) => {
		const variables = {id: userId};
		const api = 'champions';
		const query = `
		query getUser($id: String!) {
			userById(id: $id) {
				id
				name
				email
			}
		}
		`;
		fetchGraph(query, variables, api, (data) => resolve(data));
	});
}

export default getUser;
