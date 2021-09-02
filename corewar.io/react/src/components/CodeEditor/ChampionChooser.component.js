import React from 'react';
import PropTypes from 'prop-types';

import * as firebase from 'firebase/app';

import DialogTitle from '@material-ui/core/DialogTitle';
import DialogContent from '@material-ui/core/DialogContent';
import Divider from '@material-ui/core/Divider';
import RadioGroup from '@material-ui/core/RadioGroup';

import UserChampList from './UserChampList.component';

const ChampionChooser = (props) => {
	const title = 'Champion Chooser';

	return (
		<div className='champions-lists'>
			<div>
				<DialogTitle children={title} />
				<Divider />
				<DialogContent>
					<RadioGroup onChange={props.chooser}>
						<UserChampList id={"zhI9t64KhjV5qaRLeZJN"} />
					</RadioGroup>
				</DialogContent>
			</div>
			<div>
				<DialogTitle children="My champions" />
				<Divider />
				<DialogContent>
					<RadioGroup onChange={props.chooser}>
					{
						firebase.auth().currentUser
						?
						<UserChampList id={firebase.auth().currentUser.uid} />
						: null
					}
					</RadioGroup>
				</DialogContent>
			</div>
		</div>
	);
};

ChampionChooser.propTypes = {
	choosen: PropTypes.func
};

export default ChampionChooser;
