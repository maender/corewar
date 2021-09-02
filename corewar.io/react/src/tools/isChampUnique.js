import { fetchGraph } from './GraphTools';

const isChampUnique = async (name) => {
	return new Promise((resolve, reject) => {
		const variables = {name};
		const api = 'champions';
		const query = `
		query isChampUnique($name: String!) {
			isChampUnique(name: $name) {
				result
			}
		}
		`;
		fetchGraph(query, variables, api, (data) => resolve(data));
	});
}

export default isChampUnique;
