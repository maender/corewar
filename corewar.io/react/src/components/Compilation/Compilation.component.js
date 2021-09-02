import React, { useState, useEffect } from 'react';

import * as firebase from 'firebase/app';
import { fetchGraph } from '../../tools/GraphTools';
import gql from 'graphql-tag';
import { Query } from 'react-apollo';

import Loading from '../Loading/Loading.component';
import ChampionForm from '../CodeEditor/ChampionForm.component';
import RadioGroup from '@material-ui/core/RadioGroup';
import Button from '@material-ui/core/Button';

const Compilation = (props) => {
	const save = props.location.state.saved;
	const [loading, setLoading] = useState(false);
	const [winner, setWinner] = useState(null);
	const [winnerOutput, setWinnerOutput] = useState(null);
	const GET_CHAMPS = gql`
	query champs {
		champs {
			basename
		}
	}
	`;

	useEffect(() => {
		console.log(`Enter or update Compilation`);
		window.scrollTo(0, 0);
	}, []);

	const fightChampion = async (champ) => {
		if (!loading) {
			setLoading(true);
			const query = `
			query fight($champ1: String!, $champ2: String!) {
				fight(champ1: $champ1, champ2: $champ2) {
					id
					challenger
					opponent
					winner
					stdout
					err
				}
			}
			`;
			const variables = {champ1: save.basename, champ2: champ};
			const api = 'champions';
			await fetchGraph(query, variables, api, (data) => {
				if (data.fight.err){
					setWinner(null);
					setWinnerOutput(null);
					return ;
				}
				setWinner(data.fight.winner);
				setWinnerOutput(data.fight.stdout);
			})
			setTimeout(() => {
				setLoading(false);
			}, 200);
		}
	}

	const challengeEverybody = async () => {
		if (!loading) {
			setLoading(true);
			const query = `
			query challengeEverybody($challenger: String!, $userid: String!) {
				challengeEverybody(challenger: $challenger, userid: $userid) {
					id
					err
					errCode
				}
			}
			`;
			const variables = {challenger: save.basename, userid: firebase.auth().currentUser.uid};
			const api = 'champions';
			await fetchGraph(query, variables, api, (data) => {
				console.log(data);
				props.history.push({
					pathname: '/compilation-result',
					state: {data: data.challengeEverybody}
				});
			});
			setLoading(false);
		}
	}

	return (
		<div className='flex main-card'>
			<h5>Compilation Result: OK</h5>
			{
				winner
				?
				<h3>{winner} has won!</h3>
				: null
			}
			{
				winnerOutput
				?
				<pre style={{maxHeight: '100px', overflow: "scroll"}}>output: {winnerOutput}</pre>
				: null
			}
			<h5>Who do you want to challenge:</h5>
			<div>
			{
				loading
					? <Loading loadingHeight={'300px'} width={300} height={300} />
					:
				<Query query={GET_CHAMPS}>
					{({loading, error, data}) => {
						if (loading)
							return <Loading loadingHeight={'300px'} width={300} height={300} />
						else if (error)
							return <h5 style={{color: 'red'}}>{error.message}</h5>
						else {
							if (data && data.champs && data.champs[0].basename !== null) {
								return (
									<RadioGroup style={{display: 'flex', flexDirection: 'row', marginBottom: "20px", width: '70vw'}} onChange={(event, value ) => fightChampion(value)}>
										{
											data.champs.map((champ, index) => <ChampionForm key={index} champ={champ} />)
										}
									</RadioGroup>
								)
							}
							else
								return 'No champs';
						}
					}}
				</Query>
			}
			</div>
			<Button style={{margin: "20px"}} className="btn" onClick={challengeEverybody}>
				Challenge everybody
			</Button>
		</div>
	);
}

export default Compilation;
