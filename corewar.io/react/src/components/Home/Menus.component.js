import React from 'react';

import { Link } from 'react-router-dom';
import Button from '@material-ui/core/Button';

import '../../css/Menus.css';

export const StartMenu = () => (
	<div className='flex card'>
		<h1>Welcome to Corewar</h1>
		<p>As Wikipedia says:</p>
		<code>"Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode."</code>
		<p>On Corewar.io, you can edit your own warrior and fight against others players warriors</p>
		<p>The project runs on <strong>React</strong> with <strong>NodeJS / GraphQL</strong> server and database is gently hosted by <strong>Google</strong> on <strong>Firebase</strong></p>
		<Link className='link' to='code-editor'>
			<Button className='btn'>
				Create Warrior
			</Button>
		</Link>
	</div>
);

const loginList = [
	{login: 'edjubert', href: 'https://gitlab.com/DouDzZz'},
	{login: 'fldoucet', href: 'https://gitlab.com/AlphaBril'},
	{login: 'maabou-h', href: 'https://gitlab.com/mahabou'},
	{login: 'sdincbud', href: 'https://gitlab.com/Sdincbud'}
]

const loginLink = (coder, index) => (
	<a key={index} className='coder' href={coder.href} target='_blank' rel="noopener noreferrer">
		<strong>
			{coder.login}
		</strong>
		<br />
	</a>
);

export const AboutMenu = () => (
	<div className='card'>
		<h1>About Us</h1>
		<p>This website is part of 42's Corewar project</p>
		<p>Here is the project <a target='_blank' rel="noopener noreferrer" href='https://cdn.intra.42.fr/pdf/pdf/30/corewar.fr.pdf'>subject</a> (in French)</p>
		<p>Here are the corewar_fuuusiooon team members:</p>
		<div className='coderList'>
		{
			loginList.map((coder, index) => loginLink(coder, index))
		}
		</div>
	</div>
);
