import React from 'react';
import PropTypes from 'prop-types';

import gql from 'graphql-tag';
import * as firebase from 'firebase/app';
import { Query } from 'react-apollo';

import Loading from '../Loading/Loading.component';
import ChampionForm from './ChampionForm.component';

const UserChampList = (props) => {
	const GET_MY_CHAMPS = gql`
	query userChamps($id: String!) {
		userChamps(id: $id) {
			id
			basename
		}
	}
	`;

	return (
		<Query query={GET_MY_CHAMPS} variables={{id: props.id}} >
			{({loading, error, data}) => {
				const shouldShowLoading = loading && firebase.auth().currentUser;
				if (shouldShowLoading)
					return <Loading loadingHeight={'100px'} width={100} height={100} />
				else if (error) {
					return <h5 style={{color: 'red'}}>{error.message}</h5>
				} else {
					if (data && data.userChamps && data.userChamps[0].basename !== null)
						return data.userChamps.map(champ => <ChampionForm key={champ.id} champ={champ} />)
					else
						return 'No champs';
				}
			}}
		</Query>
	)
}

UserChampList.propTypes = {
	id: PropTypes.string
}

export default UserChampList;
