import { makeExecutableSchema } from 'graphql-tools';
import { PubSub, withFilter } from 'graphql-subscriptions';

import champ from '../controller/champions/champ';
import champs from '../controller/champions/champs';
import userChamps from '../controller/champions/userChamps';
import compile from '../controller/compilation/compile';
import fight from '../controller/fight/fight';
import userByEmail from '../controller/users/userByEmail';
import userById from '../controller/users/userById';
import isChampUnique from '../controller/champions/isChampUnique';
import saveChampion from '../controller/champions/saveChampion';
import updateChampion from '../controller/champions/updateChampion';
import challengeEverybody from '../controller/fight/challengeEverybody';
import challenges from '../controller/fight/challenges';
import signup from '../controller/users/signup';

import typeDefs from '../typeDefs/typedefs';

const pubsub = new PubSub();

export const resolvers = {
	Query: {
		champs,
		champ,
		compile,
		fight,
		userByEmail,
		userById,
		userChamps,
		isChampUnique,
		saveChampion,
		updateChampion,
		challengeEverybody,
		challenges,
		signup
	},
}

export const corewarSchema = makeExecutableSchema({
	typeDefs,
	resolvers,
});
