import React from 'react';

import {StartMenu, AboutMenu} from './Menus.component.js';

const Home = () => (
	<div className='flex main-card'>
		<StartMenu />
		<AboutMenu />
	</div>
);

export default Home;
