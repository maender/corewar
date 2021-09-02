import React, { useState, useEffect } from 'react';
import PropTypes from 'prop-types';
import { Link } from 'react-router-dom';
import * as firebase from 'firebase/app';

import * as ROUTES from '../../constants/routes';

import '../../css/Header.css';
import logo from '../../logo.svg';
import login from '../../login.png';
import logout from '../../logout.png';
import profile from '../../profile.png';
import home from '../../home.png';
import edit from '../../edit.png';

const ConditionnalLink = (props) => {
	const {condition, route, logo, title, alt} = props;
	return (
		condition
		?
			<Link className='' to={route} >
				<img className="right-logo" src={logo} alt={alt} title={title} />
			</Link>
		: null
	)
}

const ConditionnalBtn = (props) => {
	const {condition, click, logo, title, alt} = props;
	return (
		condition
		?
			<div className='' onClick={click}>
				<img className="right-logo" src={logo} alt={alt} title={title} />
			</div>
		: null
	)
}

ConditionnalLink.propTypes = {
	condition: PropTypes.bool,
	route: PropTypes.string,
	logo: PropTypes.string,
	title: PropTypes.string,
	alt: PropTypes.string
}

ConditionnalBtn.propTypes = {
	condition: PropTypes.bool,
	click: PropTypes.func,
	logo: PropTypes.string,
	title: PropTypes.string,
	alt: PropTypes.string
}

const Header = (props) => {
	const [logBtn, setLogBtn] = useState(true);
	const [signoutBtn, setSignoutBtn] = useState(false);
	const [userBtn, setUserBtn] = useState(false);
	const [homeBtn, setHomeBtn] = useState(false);
	const [editorBtn, setEditorBtn] = useState(false);
	const [curr, setCurr] = useState(null);

	useEffect(() => {
		console.log(`Enter or update Header`);
		setCurr(firebase.auth().currentUser);
		const setBtns = (func, route, firebaseCondition) => {
			if (firebaseCondition === 1)
				props.location.pathname === route || firebase.auth().currentUser ? func(false) : func(true);
				else if (firebaseCondition === 2)
				props.location.pathname === route || !firebase.auth().currentUser ? func(false) : func(true);
			else
				props.location.pathname === route ? func(false) : func(true);
		}
		setBtns(setLogBtn, ROUTES.LOGIN, 1);
		setBtns(setUserBtn, ROUTES.PROFILE, 2);
		setBtns(setHomeBtn, ROUTES.LANDING, 0);
		setBtns(setEditorBtn, ROUTES.CODE_EDITOR, 0);
		curr ? setSignoutBtn(true) : setSignoutBtn(false);
	}, [setCurr, curr, props.location.pathname])

	const _signOut = () => {
		setLogBtn(true);
		firebase.auth().signOut();
		setCurr(null);
		props.history.push('/');
	}

	return (
		<header className='header'>
			<div>
				<Link to='/' className='home-link home-title'>
					<img className='header-logo' src={logo} alt='Logo' title='Corewar.io' />
					<span className='header-title'>Corewar</span>
				</Link>
			</div>
			<div className='right-links'>
				<ConditionnalLink condition={userBtn} route={ROUTES.PROFILE} logo={profile} alt="profile" title="Profile" />
				<ConditionnalLink condition={editorBtn} route={ROUTES.CODE_EDITOR} logo={edit} alt="code-editor" title="Code Editor" />
				<ConditionnalLink condition={homeBtn} route={ROUTES.LANDING} logo={home} alt="home" title="Home" />
				<ConditionnalBtn condition={signoutBtn} click={_signOut} logo={logout} alt="logout" title='Logout' />
				<ConditionnalLink condition={logBtn} route={ROUTES.LOGIN} logo={login} alt="Login" title='Login' />
			</div>
		</header>
	)
}

export default Header;
