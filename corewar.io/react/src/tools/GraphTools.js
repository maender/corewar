const host = process.env.REACT_APP_DOCKER_HOST || 'localhost';
const port = process.env.REACT_APP_DOCKER_NODE_PORT || '4000';

export const fetchGraph = (query, variables, api, callback, signal) => {
	fetch(`http://${host}:${port}/${api}`, {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json',
		},
		body: JSON.stringify({
			query,
			variables
		}),
	}, {signal})
	.then(response => response.json())
	.then(responseAsJson => {
		if (responseAsJson.errors) throw console.error(`Errors: ${responseAsJson.errors[0].message}`);
		callback(responseAsJson.data)
	})
	.catch(err => console.error(err));
}
