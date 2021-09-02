import React from 'react';

import { Link } from 'react-router-dom';

import '../../css/Footer.css';

const Footer = () => (
	<footer className='Footer'>
		<Link className="link" to='/about'>About us</Link>
		<div><i>corewar_fuuusiooon@2019</i></div>
	</footer>
)

export default Footer;
