import { useState, useEffect } from 'react';

const usePromise = (promiseOrFunction, defaultValue) => {
	const [state, setState] = useState({value: defaultValue, error: null, isPending: true});

	useEffect(() => {
		console.log(`Enter or update usePromise`);
		const promise = (typeof promiseOrFunction === 'function')
			? promiseOrFunction()
			: promiseOrFunction;

		let isSubscribed = true;
		promise
			.then(value => isSubscribed ? setState({value, error: null, isPending: false}) : null)
			.catch(error => isSubscribed ? setState({value: defaultValue, error, isPending: true}) : null);
		return () => (isSubscribed = false)
	}, [promiseOrFunction, defaultValue]);

	const { value, error, isPending } = state;
	return [ value, error, isPending ];

}

export default usePromise;
