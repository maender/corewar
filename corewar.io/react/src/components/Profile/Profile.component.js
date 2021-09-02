import React, {useState, useEffect} from 'react';

import { fetchGraph } from '../../tools/GraphTools';
import * as firebase from 'firebase/app';

import '../../css/Profile.css';
import defaultProfile from '../../default_profile.jpg';

import MyChampList from './MyChampList.component';
import MyProfile from './MyProfile.component';
import MyChallengesList from './MyChallengesList.component';

const Profile = (props) => {
	const [username, setUsername] = useState('Username');
	const [email, setEmail] = useState('Email');
	const [userid, setUserid] = useState('User Id');
	const [avatar, setAvatar] = useState(defaultProfile);
	const [loading, setLoading] = useState(true);

	const userCb = (data) => {
		console.log(data);
		setUserid(data.userById.id);
		setUsername(data.userById.name ? data.userById.name : username);
		setEmail(data.userById.email ? data.userById.email : email);
		setAvatar(data.userById.avatar ? data.userById.avatar : avatar);
		setLoading(false);
	}

	const getUserData = async (signal) => {
		if (!firebase.auth().currentUser)
			return props.history.push('/login');
		const query = `
		query user($id: String!) {
			userById(id: $id) {
				id
				name
				email
				avatar
			}
		}`;
		const variables = {id: firebase.auth().currentUser.uid};
		const api = 'champions';

		if (loading)
			await fetchGraph(query, variables, api, userCb, signal);
	}

	useEffect(() => {
		console.log(`Enter or update Profile`);
		const controller = new AbortController();
		const signal = controller.signal;

		getUserData(signal);
		return controller.abort();
	}, []);

	return (
		<div className='flex main-card'>
			<h1>Hello {username}</h1>
			<div className='panes'>
				<div>
					<MyChampList userid={userid} {...props} />
				</div>
				<div>
					<MyChallengesList userid={userid} {...props} />
				</div>
				<div>
					<MyProfile userid={userid} username={username} email={email} avatar={avatar} />
				</div>
			</div>
		</div>
	);
};

export default Profile;
