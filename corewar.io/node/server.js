import express from 'express';
import graphlHTTP from 'express-graphql';
import { createServer } from 'http';
import { execute, subscribe } from 'graphql';
import { SubscriptionServer } from 'subscriptions-transport-ws';
import cors from 'cors';
import { populateIfZero } from './controller/firebase/populate.firebase';

const port = process.env.PORT || 4000;

import { corewarSchema } from './schema/corewarSchema';

populateIfZero();

const app = express();

app.use(cors());
app.options('*', cors());

app.use('/champions', graphlHTTP({
	schema: corewarSchema,
	endpointURL: 'champs',
	subscriptionsEndpoint: `ws://localhost:${port}/subscriptions`,
	graphiql: true
}));

app.get('/', function (req, res) {
	res.send('Hello World!')
})

const ws = createServer(app);

ws.listen(port, () => {
	console.log(`Express GraphQL Server now running on localhost:${port}/`);

	new SubscriptionServer({
		execute,
		subscribe,
		corewarSchema,
	}, {
		server: ws,
		path: '/subscriptions'
	});
});
