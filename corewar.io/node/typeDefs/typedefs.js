
const typeDefs = `
	type Query {
		champ(basename: String!): Champ,
		champs: [Champ],
		compile(id: String!, userid: String!): CompilationResult
		fight(champ1: String!, champ2: String!): Winner,
		userByEmail(email: String!): User,
		userById(id: String!): User,
		userChamps(id: String!): [Champ],
		isChampUnique(name: String!): BoolReturn,
		saveChampion(name: String!, userid: String!, content: String!): Champ,
		updateChampion(name: String!, userid: String!, content: String!): Champ,
		challengeEverybody(challenger: String!, userid: String!): Channel
		challenges(id: String!): [Channel]
		signup(userid: String!, name: String!, email: String!): BoolReturn
	},

	type CompilationResult {
		stdout:		String
		stderr:		String
		err:		String
		errCode:	Int
	},

	type BoolReturn {
		result:		Boolean
		err:		String
		errCode:	Int
	},

	type Channel {
		id:			String
		timestamp:	Float
		stat:		Float
		total:		Int
		err:		String
		errCode:	String
	},

	type Winner {
		id:			String
		winner:		String
		challenger:	String
		opponent:	String
		stdout:		String
		err:		String
		errCode:	Int
	},

	type Champ {
		id:			String
		basename:	String
		path:		String
		timestamp:	String
		lastUpdate:	String
		content:	String
		ownerId:	String
		err:		String
		errCode:	Int
	},

	type User {
		id:			String
		name:		String
		email:		String
		avatar:		String
		err:		String
		errCode:	Int
	}
`;

export default typeDefs;
