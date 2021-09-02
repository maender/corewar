import React, { useState, useEffect } from 'react';
import PropTypes from 'prop-types';
import * as firebase from 'firebase/app';
import 'firebase/storage';

import FileUploader from 'react-firebase-file-uploader';
import { CircularProgressbar, buildStyles } from 'react-circular-progressbar';
import 'react-circular-progressbar/dist/styles.css';

import defaultProfile from '../../default_profile.jpg';
import Button from '@material-ui/core/Button';

const MyProfile = (props) => {
	const [pp, setPp] = useState(defaultProfile);
	const [progress, setProgress] = useState(0);
	const [uploading, setUploading] = useState(false);
	const [user, setUser] = useState({
		username: 'Username',
		email: 'Email',
		avatar: defaultProfile,
		userid: 'User Id'
	});

	const changePP = (value) => {
		let files = null;
		const formData = new FormData();
		console.log(value);
		if (value && value.target && value.target.files)
			files = Array.from(value.target.files);
		console.log(files);
		if (files) {
			files.forEach((file, i) => {
				const fr = new FileReader();
				fr.onload = (e1) => {
					console.log('e1: ', e1);
					console.log('e1.target: ', e1.target);
				}
				const res = fr.readAsDataURL(file);
				console.log(res);
			});
		}
	}

	const handleUploadStart = () => {
		setUploading(true);
		console.log('upload Starting');
	}

	const handleUploadError = (err) => {
		console.error(err);
	}

	const handleProgress = (prog) => {
		setProgress(prog);
		console.log(prog);
	}

	const handleUploadSuccess = (filename) => {
		const userid = firebase.auth().currentUser.uid;
		console.log(`upload success: ${filename}`);
		firebase.storage().ref(`images/${userid}/${filename}`)
		.getDownloadURL()
		.then(url => {
			setUser({...user, avatar: url})
			firebase.firestore().collection('users').doc(userid).update({avatar: url})
			.then(() => {
				setTimeout(() => {
					setUploading(false);
				}, 1000)
			});
		})
	}

	const saveUsername = () => {
		if (props.username !== user.username) {
			firebase.firestore().collection('users').doc(user.userid).update({
				name: user.username
			}).then(() => window.location.reload())
		}
	}

	useEffect(() => {
		const {username, email, avatar, userid} = props;
		if (props.username !== 'Username' && props.email !== 'Email')
			setUser({username, email, avatar, userid});
	}, [props]);

	return (
		<div>
			<h2>My Profile</h2>
			<div className='profileList'>
				<label>
					<div className='img-div'>
					{
						uploading
						?
						<CircularProgressbar
							value={progress}
							text={progress < 100 ? `${progress}%` : 'OK !'}
							className='progressBar'
							styles={buildStyles({
								textColor: '#a70000',
								trailColor: '#bbbbbb',
								pathColor: `rgba(167, 0, 0, ${progress})`
							})} />
						:
						<img src={user.avatar} alt='profile' title='You' className="pp" />
					}
					</div>
					<FileUploader
						hidden
						accept='image/*'
						storageRef={firebase.storage().ref(`images/${firebase.auth().currentUser.uid}`)}
						onUploadStart={handleUploadStart}
						onUploadError={handleUploadError}
						onUploadSuccess={handleUploadSuccess}
						onProgress={handleProgress} />
				</label>
				{/* <input type='file' id='profile-picture' onChange={changePP} /> */}
				<input value={user.username} onChange={(username) => {
					setUser({...user, username: username.target.value})}} />
				<p className='email-address'>{user.email}</p>
				<Button disabled={props.username === user.username || user.username.length < 4} onClick={saveUsername} className='btn'>Save usersame</Button>
			</div>
		</div>
	)
}

MyProfile.propTypes = {
	userid: PropTypes.string.isRequired,
	username: PropTypes.string.isRequired,
	email: PropTypes.string.isRequired,
	avatar: PropTypes.string.isRequired
}

export default MyProfile;
