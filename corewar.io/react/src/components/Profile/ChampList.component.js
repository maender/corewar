import React from 'react';
import PropTypes from 'prop-types';

import * as ROUTES from '../../constants/routes';

const ChampList = (props) => {
	const editChamp = (champ) => {
		console.log(props);
		console.log(champ);
		props.history.push({
			pathname: ROUTES.CODE_EDITOR,
			state: {
				edit: champ
			}
		});
	}

	return (
		<div className='list'>
			{
				props.champs.map((champ) => {
					return (
						<div onClick={() => editChamp(champ)} className="champ" key={champ.id}>
							<p>{champ.basename}</p>
						</div>
					);
				})
			}
		</div>
	)
};

ChampList.propTypes = {
	champs: PropTypes.array.isRequired
}

export default ChampList;
