import React, { useEffect, useState } from 'react';
import PropTypes from 'prop-types';

import * as firebase from 'firebase/app';
import { fetchGraph } from '../../tools/GraphTools';

import Loading from '../Loading/Loading.component';
import Button from '@material-ui/core/Button';
import getUser from '../../tools/getUser';
import DialogTitle from '@material-ui/core/DialogTitle';
import DialogContent from '@material-ui/core/DialogContent';
import Divider from '@material-ui/core/Divider';
import isChampUnique from '../../tools/isChampUnique';
import useDebounce from '../../tools/useDebounce';
import RadioGroup from '@material-ui/core/RadioGroup';

import UserChampList from './UserChampList.component';

import '../../css/Compile.css';

const SaveChampion = (props) => {
	const [name, setName] = useState('default_'+Date.now());
	const [loading, setloading] = useState(false);
	const [canSave, setCansave] = useState(true);
	const [checking, setChecking] = useState(true);
	const [saving, setSaving] = useState(false);
	const debounceName = useDebounce(name, 500);

	const checkIfExists = (toCheck) => {
		if (toCheck) {
			setChecking(true);
			isChampUnique(toCheck).then(data => {
				setChecking(false);
				if (data.isChampUnique)
					setCansave(!data.isChampUnique.result);
			})
		}
		else {
			setChecking(false);
		}
	}

	const compileChamp = async (state) => {
		const userid = firebase.auth().currentUser.uid;
		const query = `
		query compileChamp($id: String!, $userid: String!) {
			compile(id: $id, userid: $userid) {
				stdout
				stderr
				err
				errCode
			}
		}
		`;
		const variables = {id: state.saved.id, userid};
		const api = 'champions';
		console.log(state);

		await fetchGraph(query, variables, api, (data) => {
			state.data = data;
			if (data.compile.stderr)
				alert(data.compile.stderr);
			console.log(data.compile);
			if (data.compile.stdout
				&& data.compile.stdout.search("Writing output program to") === 0) {
				setSaving(false);
				props.history.push({
					pathname: '/compilation',
					state
				});
			}
			else {
				setSaving(false);
				if (data.compile.stdout)
					alert(`Compilation returns: ${data.compile.stdout}`);
				else
					alert(`Error (${data.compile.errCode}): ${data.compile.err}`);
			}
		});
		if (saving)
			setSaving(false);
	}

	const saveChampion = async () => {
		const id = await firebase.auth().currentUser.uid;
		const query = `
		query saveChampion($name: String!, $id: String!, $content: String!) {
			saveChampion(name: $name, userid: $id, content: $content) {
				id
				basename
				content
				ownerId
				err
				errCode
			}
		}
		`;
		const variables = {name, id, content: props.content};
		const api = 'champions';
		if (!saving) {
			setSaving(true);
			await fetchGraph(query, variables, api, (data) => compileChamp({variables, id, saved: data.saveChampion}));
		}
	}

	useEffect(() => {
		console.log(`Enter or update SaveChampion`);
		if (name === 'default') {
			if (!loading) {
				setloading(true);
				const user =  getUser();
				if (user.userById) {
					setName(user.userById.name + '_killer');
				}
				setloading(false);
			}
		}
		else
			checkIfExists(debounceName);
	}, [debounceName, name, loading]);

	const updateChampion = async (event, value) => {
		const id = await firebase.auth().currentUser.uid;
		const query = `
		query updateChampion($name: String!, $id: String!, $content: String!) {
			updateChampion(name: $name, userid: $id, content: $content) {
				id
				basename
				err
				errCode
			}
		}
		`;
		const variables = {name: value, id, content: props.content};
		const api = 'champions';

		if (!saving) {
			setSaving(true);
			await fetchGraph(query, variables, api, (data) => {
				console.log(data.updateChampion);
				compileChamp({variables, id, saved: data.updateChampion});
			});
		}
	}

	const ChampionNaming = () => (
		<div className='saving-div'>
			<div className='naming-champion'>
				<h5>How your killer should be called:</h5>
				<input disabled={saving} value={name} onChange={(newName) => setName(newName.target.value)} autoFocus style={{margin: '10px'}} />
				{canSave ? <span className='already-exists'>Champion name already exists</span> : null}
				<Button className='btn' disabled={canSave || saving || checking} onClick={saveChampion} >
					{checking || saving ? <Loading loadingHeight={'100px'} width={50} height={50} /> : 'Save'}
				</Button>
			</div>
			<div className='naming-champion'>
				<h5>Or save another file</h5>
				<RadioGroup onChange={updateChampion}>
					<UserChampList id={firebase.auth().currentUser.uid} />
				</RadioGroup>
			</div>
		</div>
	);

	return (
		<div>
			<DialogTitle>
				Save your champion
			</DialogTitle>
			<Divider />
			<DialogContent>
				{loading ? <Loading loadingHeight={'300px'} /> : <ChampionNaming />}
			</DialogContent>
		</div>
	)
};

SaveChampion.propTypes = {
	content: PropTypes.string
};

export default SaveChampion;
