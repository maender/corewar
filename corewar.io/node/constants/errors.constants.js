const NOT_FOUND = {err: 'not found', errCode: 404};
const QUERY_ERROR = {err: 'query error', errCode: 400};
const ERR = (err) => {return {err: err.message, errCode: err.code}};

export {
	NOT_FOUND,
	QUERY_ERROR,
	ERR
};