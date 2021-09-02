import React from 'react';
import {
	Route,
	Switch,
	Redirect
} from 'react-router-dom';
import * as firebase		from 'firebase/app';

import * as ROUTES			from '../../constants/routes';

import Home					from '../Home/Home.component';
import CodeEditor			from '../CodeEditor/CodeEditor.component';
import Login				from '../Login/Login.component';
import Profile				from '../Profile/Profile.component';
import About				from '../About/About.component';
import Compilation			from '../Compilation/Compilation.component';
import CompilationResult	from '../Compilation/CompilationResult.component';

const loginRedirect = Component => props => {
	return (firebase.auth().currentUser
		? <Redirect to="/" />
		: <Component {...props} />)
}

const LoginRedirect = loginRedirect(Login);

const Routing = (props) => (
	<Switch>
		<Route path={ ROUTES.LANDING }			exact component={ Home } />
		<Route path={ ROUTES.PROFILE }			exact component={ Profile }				{ ...props } />
		<Route path={ ROUTES.LOGIN }			exact>
			<LoginRedirect { ...props } />
		</Route>
		<Route path={ ROUTES.COMPILATION_RES }	exact component={ CompilationResult } />
		<Route path={ ROUTES.COMPILATION }		exact component={ Compilation } />
		<Route path={ ROUTES.ABOUT }			exact component={ About } />
		<Route path={ ROUTES.CODE_EDITOR }		exact component={ CodeEditor } { ...props } />
		<Route>
			<Redirect to="/" />
		</Route>
	</Switch>
);

export default Routing;
