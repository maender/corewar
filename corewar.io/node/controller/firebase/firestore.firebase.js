const admin = require('firebase-admin');

let serviceAccount = './corewar-firebase-adminsdk-711nk-3c3b3057fa.json';

admin.initializeApp({
	apiKey: "AIzaSyBc5HYmEhtDBAVbs1gokhPI9DK8vqtFSzg",
	authDomain: "corewar.firebaseapp.com",
	databaseURL: "https://corewar.firebaseio.com",
	projectId: "corewar",
	storageBucket: "corewar.appspot.com",
	messagingSenderId: "1074935191690",
	appId: "1:1074935191690:web:946d6b7f2cdfff7e",
	credential: admin.credential.cert(serviceAccount)
});

export const db = admin.firestore();
export const realtimeDB = admin.database();
