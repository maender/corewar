import React from 'react';
import PropTypes from 'prop-types';

import loadingImg from '../../loading.gif';

const Loading = (props) => {
	return (<div style={{
		display: "flex",
		height: props.loadingHeight || '80vh',
		flexDirection: "column",
		justifyContent: "center",
		alignItems: "center"
	}}>
		<img src={loadingImg} alt="loading" style={{
			width: props.width+'px' || '100px',
			height: props.height+'px' || '100px'
		}} />
	</div>);
};

Loading.propTypes = {
	loadingHeight: PropTypes.string,
	width: PropTypes.number,
	height: PropTypes.number
}

export default Loading;
