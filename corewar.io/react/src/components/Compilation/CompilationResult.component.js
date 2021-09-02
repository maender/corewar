import React, { useState } from 'react';

import * as firebase from 'firebase';
// import 'firebase/firestore';
// import 'firebase/database';

import Dialog from '@material-ui/core/Dialog';
import '../../css/Compile.css'

const Result = (props) => {
	return (
		<div className='result'>
			<h1>Result</h1>
			<strong>Fight nº{props.currIndex + 1}</strong>
			<span><strong>Winner</strong>: {props.selected.winner}</span>
			<span><strong>Challenger</strong>: {props.selected.challenger}</span>
			<span><strong>Opponent</strong>: {props.selected.opponent}</span>
			<span><strong>stdout</strong>: <br/>
			<div className='result-output'><pre><code>{props.selected.stdout}</code></pre></div></span>
		</div>
	);
}

const DataRender = (props) => (
	<div className={`${props.class}s`}>
	{
		props.challenge.map((data, index) => {
			let condition = 1;
			if (props.class === 'winner')
				condition = data.winner === data.challenger;
			else
				condition = data.winner !== data.challenger;

			if (condition) {
				return (
					<div onClick={() => props.toggler(data, index)} key={index}>
					{
						<div className={`data ${props.class}`}>
							<strong>Fight nº{index + 1}</strong>
							<span><strong>Winner</strong>: {data.winner === data.challenger ? 'You !' : data.winner}</span>
							<span><strong>Opponent</strong>: {data.opponent}</span>
						</div>
					}
					</div>
				)
			}
			else return null
		})
	}
	</div>
);

const PrintData = (props) => {
	return (
		<div className='dataGrid'>
			<DataRender class='winner' challenge={props.challenge} toggler={props.toggler} />
			<DataRender class='looser' challenge={props.challenge} toggler={props.toggler} />
		</div>
	)
}

const StrongCode = (props) => (
	<strong>
		<code>
			{props.value}
		</code>
	</strong>
);

const PrintStats = (props) => (
	<div>
		<h1>Compilation Result</h1>
		<h2>Fight {props.challengeStats.total} on {props.totalOpponent}</h2>
		<h3>Current opponent: <code>{props.pendingData ? props.currOpponent : null}</code></h3>
		<p>On <StrongCode value={props.challengeStats.total} /> matches, you won <StrongCode value={props.challengeStats.won} /> match for <StrongCode value={props.challengeStats.loose} /> loose</p>
		<p>Stat: <strong><code>{props.challengeStats.percent}%</code></strong> won</p>
	</div>
)

const CompilationResult = (props) => {
	const [challenge, setChallenge] = useState([]);
	const [pendingData, setPending] = useState(false);
	const [currOpponent, setCurrOpponent] = useState('');
	const [totalOpponent, setTotalOpponent] = useState(0);
	const [challengeStats, setChallengeStats] = useState({});
	const [selected, setSelected] = useState(null);
	const [resultDialog, setResultDialog] = useState(false);
	const [currIndex, setCurrIndex] = useState(null);

	const getChallengeData = (result) => {
		let total = 0;
		let won = 0;
		let loose = 0;
		let percent = 0;

		if (result) {
			total = result.length;
			result.map((data) => data.winner === data.challenger ? won++ : loose++);
			percent = won / total * 100;
			if (isNaN(percent))
				percent = 0;
			let fixed = percent.toFixed(2);
			setChallengeStats({ total, won, loose, percent: fixed });
		}
	}

	const toggleResult = (data, index) => {
		if (data)
			setSelected(data);
		else
			setSelected(null);
		if (index)
			setCurrIndex(index);
		else
			setCurrIndex(null);
		setResultDialog(!resultDialog);
	}


	React.useEffect(() => {
		console.log(`Enter or update CompilationResult`);
		const channelId = props.location.state.data.id;
		const path = `challenges/${firebase.auth().currentUser.uid}/${channelId}`;

		// firebase.database().ref('salut').set({allright: 'salut'})
		firebase.database().ref(path).on('value', snapshot => {
			if (snapshot && snapshot.val()) {
				setPending(snapshot.val().pending);
				setCurrOpponent(snapshot.val().currOpponent);
				getChallengeData(snapshot.val().result);
				setChallenge(snapshot.val().result);
				setTotalOpponent(challengeStats.total > snapshot.val().totalOpponent ? challengeStats.total : snapshot.val().totalOpponent);
			}
		});

		// const unsubscribe = firebase.firestore().collection('challenges').doc(channelId)
		// .onSnapshot(snapshot => {
		// 	if (snapshot.data()) {
		// 		setPending(snapshot.data().pending);
		// 		setCurrOpponent(snapshot.data().currOpponent);
		// 		getChallengeData(snapshot.data().result);
		// 		setChallenge(snapshot.data().result);
		// 		setTotalOpponent(challengeStats.total > snapshot.data().totalOpponent ? challengeStats.total : snapshot.data().totalOpponent);
		// 	}
		// }, (err) => console.error(err));
		// return () => unsubscribe();
	}, [])

	return (
		<div className='flex main-card'>
			<PrintStats challengeStats={challengeStats} totalOpponent={totalOpponent} />
			<div className='result'>
				<PrintData challenge={challenge} toggler={toggleResult} />
			</div>
			<Dialog open={resultDialog} onBackdropClick={toggleResult}>
				<Result currIndex={currIndex} selected={selected} />
			</Dialog>
		</div>
	)
}

export default CompilationResult;
