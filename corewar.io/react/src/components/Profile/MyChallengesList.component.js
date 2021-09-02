import React, { useEffect, useState } from 'react';
import { fetchGraph } from '../../tools/GraphTools';
import { Link } from 'react-router-dom';

import * as ROUTES from '../../constants/routes';
import Button from '@material-ui/core/Button';
import Loading from '../Loading/Loading.component';

const subscribeChannel = (id, props) => {
	props.history.push({
		pathname: ROUTES.COMPILATION_RES,
		state: {
			data: {id}
		}
	});
}

const ChallengeList = (props) => {
	return (
		<div>
			<div className='list'>
				{
					props.challenges.map(challenge => {
						const date = new Date(challenge.timestamp);
						const stat = challenge.stat ? challenge.stat.toFixed(2) : 0;
						const colorClass = stat > 33 ? stat > 70 ? 'good' : 'average' : 'bad';

						console.log(colorClass);
						return (
							<div key={challenge.id} className={`challenge `+colorClass} onClick={() => subscribeChannel(challenge.id, props)}>
								<p>{date.toDateString()}</p>
								<p>Total opponent: {challenge.total}</p>
								<p>Success rate: {stat}%</p>
							</div>
						)
					})
				}
			</div>
		</div>
	);
};

const MyChallengesList = (props) => {
	const [challenges, setChallenges] = useState([]);
	const [loading, setLoading] = useState(true);
	const [noChallenges, setNoChallenges] = useState(true);

	useEffect(() => {
		console.log(`Enter or update MyChallengesList`);
		const controller = new AbortController();
		const signal = controller.signal;

		const loadChallenges = async (signal) => {
			const query = `
			query challenges($id: String!) {
				challenges(id: $id) {
					id
					timestamp
					stat
					total
					err
					errCode
				}
			}
			`;
			const variables = {id: props.userid};
			const api = 'champions';
			if (loading && props.userid !== 'User Id') {
				await fetchGraph(query, variables, api, (data) => {
					data.challenges.length > 0 && data.challenges[0].id !== null ? setNoChallenges(false) : setNoChallenges(true);
					setLoading(false);
					if (noChallenges)
						return ;
					if (data.challenges.length > 0 && data.challenges[0].id !== null) {
						const arr = [];
						data.challenges.forEach(challenge => arr.push(challenge));
						setChallenges(arr);
					}
				}, signal);
			}
		}
		loadChallenges(signal);

		return controller.abort();
	}, [loading, noChallenges, props.userid]);

	return (
		<div>
			<h2>My Challenges List</h2>
			<div className='challengelist'>
			{
				noChallenges && !loading
				? <p>You don't have run any Challenge</p>
				: <ChallengeList challenges={challenges} {...props} />
			}
			{
				loading
				? <Loading loadingHeight={'300px'} />
				: null
			}
			<Link className='btn-link' to={ROUTES.CODE_EDITOR}>
				<Button className='btn'>
					Start One
				</Button>
			</Link>
			</div>
		</div>
	);
};

export default MyChallengesList;