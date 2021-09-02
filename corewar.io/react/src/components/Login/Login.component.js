import React, { useState } from 'react';
import firebase from 'firebase/app';
import { fetchGraph } from '../../tools/GraphTools';

import '../../css/Login.css';

import Loading from '../Loading/Loading.component';

const Login = (props) => {
	let [login, setLogin] = useState(true);
	let [email, setEmail] = useState('');
	let [password, setPassword] = useState('');
	let [name, setName] = useState('');
	const [loading, setLoading] = useState(false);

	const _logUser = async () => {
		setLoading(true);
		try {
			if (firebase.auth().currentUser)
				props.history.push('/')
			firebase.auth().signInWithEmailAndPassword(email, password)
			.then(() => setLoading(false))
			.catch(err => {
				if (err.code === "auth/user-not-found")
					console.error(`ERROR: user not found: ${err.message}`);
				else if (err.code === "auth/wrong-password")
					console.error(`ERROR: wrong password: ${err.message}`);
				else
					console.error(`ERROR(${err.code}): ${err.message}`);
				setLoading(false);
			});
		} catch (e) {
			setLoading(false);
			alert(e);
		}
	}

	const _signUser = async () => {
		setLoading(true);
		firebase.auth().createUserWithEmailAndPassword(email, password)
		.then(user => {
			console.log(firebase.auth().currentUser.uid);
			const query = `
			query signup($userid: String!, $name: String!, $email: String!) {
				signup(userid: $userid, name: $name, email: $email) {
					result
				}
			}
			`
			const variables = {userid: firebase.auth().currentUser.uid, name, email};
			const api = 'champions';
			fetchGraph(query, variables, api, (result) => {
				console.log(result);
			})
			setLoading(false);
		})
		.catch(err => {
			console.error(err);
			setLoading(false);
		})
	}

	const _log = () => {
		if (login)
			_logUser();
		else
			_signUser();
	}

	return (
		<div className='card main-card'>
			{
				loading
				?
				<Loading width={100} height={100} loadingHeight={'300px'} />
				:
				<div>
					<h1 className='title'>{login ? 'Login' : 'Signup'}</h1>
					<div className='flex login-div'>
						{
							!login && (
								<input
									value={name}
									onChange={e => setName(e.target.value)}
									type="text"
									placeholder="Pseudo" />
							)
						}
						<input
							value={email}
							onChange={e => setEmail(e.target.value)}
							type="email"
							placeholder="Email" />
						<input
							value={password}
							onChange={e => setPassword(e.target.value)}
							type="password"
							placeholder="Password" />
					</div>
					<div className="flex btn-div">
						<div className='btn' onClick={() => _log()}>
							<span>{login ? 'login' : 'create account'}</span>
						</div>
						<div className='no-account' onClick={() => setLogin(!login)}>
							<span>{
								login
									? 'No account?'
									: 'Have an account?'
							}</span>
						</div>
					</div>
				</div>
			}
		</div>
	)
}

export default Login;
