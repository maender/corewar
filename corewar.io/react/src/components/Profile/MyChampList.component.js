import React, { useState, useEffect } from 'react';
import PropTypes from 'prop-types';
import { Link } from 'react-router-dom';
import { fetchGraph } from '../../tools/GraphTools';

import * as ROUTES from '../../constants/routes';
import ChampList from './ChampList.component';
import Loading from '../Loading/Loading.component';
import Button from '@material-ui/core/Button';

const MyChampList = (props) => {
	const [champs, setChamps] = useState([]);
	const [loading, setLoading] = useState(true);
	const [noChamps, setNoChamps] = useState(true);

	useEffect(() => {
		console.log(`Enter or update MyChampList`);
		const controller = new AbortController();
		const signal = controller.signal;

		const loadChamps = async (signal) => {
			const query = `
			query champs($id: String!) {
				userChamps(id: $id) {
					id
					basename
				}
			}
			`;
			const variables = {id: props.userid};
			const api = 'champions';
			if (loading && props.userid !== 'User Id') {
				await fetchGraph(query, variables, api, (data) => {
					data.userChamps.length > 0 && data.userChamps[0].id !== null ? setNoChamps(false) : setNoChamps(true);
					setLoading(false);
					if (noChamps)
						return ;
					if (data.userChamps.length > 0) {
						const arr = [];
						data.userChamps.forEach(champ => {
							arr.push(champ);
						});
						setChamps(arr);
					}
				}, signal);
			}
		}
		loadChamps(signal);

		return controller.abort();
	}, [loading, noChamps, props.userid]);

	return (
		<div>
			<h2>My Champ List</h2>
			<div className='champlist'>
				{ noChamps && !loading ? <p>You have no champion</p> : null }
				{ loading ? <Loading loadingHeight={'300px'} /> : <ChampList champs={champs} {...props} /> }
				<Link className='btn-link' to={ROUTES.CODE_EDITOR}>
					<Button className='btn'>
						Create one
					</Button>
				</Link>
			</div>
		</div>
	);
};

MyChampList.propTypes = {
	userid: PropTypes.string.isRequired
}

export default MyChampList;
