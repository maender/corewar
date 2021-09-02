import React from 'react';
import { BrowserRouter as Router, withRouter } from 'react-router-dom';

import { ApolloProvider } from 'react-apollo';
import { ApolloClient } from 'apollo-client';
import { createHttpLink } from 'apollo-link-http';
import { InMemoryCache } from 'apollo-cache-inmemory';
import { setContext } from 'apollo-link-context';

import {useAuth, userContext} from './components/Session/context';


import Header from './components/Header/Header.component';
import Footer from './components/Footer/Footer.component';
import Routing from './components/Routes/Routes.component';
import Loading from './components/Loading/Loading.component';

import './App.css';
import { AUTH_TOKEN } from './constants/token';

const host = process.env.REACT_APP_DOCKER_HOST || 'node';
const port = process.env.REACT_APP_DOCKER_NODE_PORT || '4000';
console.log(`Connecting to host ${host}:${port}`);

const httpLink = createHttpLink({
  uri: `http://${host}:${port}/champions`,
});

const authLink = setContext((_, { headers }) => {
	const token = localStorage.getItem(AUTH_TOKEN)
	return {
		headers: {
			...headers,
			authorization: token ? `Bearer ${token}` : ''
		}
	}
});

const client = new ApolloClient({
	link: authLink.concat(httpLink),
	cache: new InMemoryCache()
});

const HeaderRouted = withRouter(props => <Header {...props} />);
const RoutingProps = withRouter(props => <Routing {...props} />);

const App = () => {
	const {initializing, user} = useAuth();

	if (initializing) {
		return (<Loading width={100} height={100} />);
	}
	return (
		<Router>
			<ApolloProvider client={client}>
				<userContext.Provider value={{user}}>
					<HeaderRouted />
						<div className='App flex'>
							<RoutingProps />
						</div>
					<Footer />
				</userContext.Provider>
			</ApolloProvider>
		</Router>
	)
};

export default App;
