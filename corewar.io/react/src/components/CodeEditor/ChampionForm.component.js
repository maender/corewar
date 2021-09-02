import React from 'react';

import { FormControlLabel, Radio } from '@material-ui/core';

const ChampionForm = (props) => (
	<FormControlLabel
		value={props.champ.basename}
		control={<Radio style={{color: 'var(--primary-color)'}} /> }
		label={props.champ.basename} />
);

export default ChampionForm;
