import { useEffect, useContext, createContext, useState } from 'react';
import * as firebase from 'firebase/app';
import 'firebase/auth';

export const userContext = createContext({
	user: null
});

export const useSession = () => {
	const {user} = useContext(userContext);
	return user;
}

export const useAuth = () => {
	const [state, setState] = useState(() => {
		const user = firebase.auth().currentUser;
		return {initializing: !user, user}
	});

	const onChange = (user) => {
		setState({initializing: false, user});
	}

	useEffect(() => {
		console.log(`Enter or update context`);
		const unsubscribe = firebase.auth().onAuthStateChanged(onChange);
		return () => unsubscribe()
	}, []);

	return state;
}
