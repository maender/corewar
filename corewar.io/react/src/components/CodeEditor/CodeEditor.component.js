import React, { useState, useEffect } from 'react';

import { fetchGraph } from '../../tools/GraphTools';
import { UnControlled as CodeMirror } from 'react-codemirror2';

import * as firebase from 'firebase/app';
import 'firebase/auth';

import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';

import ChampionChooser from './ChampionChooser.component';
import SaveChampion from './SaveChampion.component';

import 'codemirror/lib/codemirror.css';
import '../../css/CodeEditor.css';
import 'codemirror/mode/gas/gas';
import 'codemirror/keymap/vim';
import 'codemirror/keymap/emacs';
import 'codemirror/keymap/sublime';

import * as ROUTES from '../../constants/routes';

const CodeEditor = (props) => {
	const defaultValue = `
; Write your code here
; You can also select a pre-loaded champ by clicking on 'LOAD CHAMPION' button
; Good luck.

.name "My Champion"
.comment "My badass comment"

`;
	const keymapArr = ['sublime', 'vim', 'emacs'];
	let [codeValue, setCodeValue] = useState(defaultValue);
	let [tempCodeValue, setTempCodeValue] = useState(defaultValue);
	let [champPopover, setChampPopover] = useState(false);
	let [savePopover, setSavePopover] = useState(false);
	let [keymap, setKeymap] = useState(0);

	const toggleChampChooser = () => {
		setChampPopover(!champPopover);
	};

	const toggleKeymap = () => {
		if (keymap + 1 < 3)
			setKeymap(++keymap);
		else
			setKeymap(0);
	}

	const toggleSave = () => {
		setCodeValue(tempCodeValue);
		if (firebase.auth().currentUser)
			setSavePopover(!savePopover);
		else
			props.history.push(ROUTES.LOGIN);
	};

	const loadChamp = (newCode) => {
		if (newCode && newCode.champ)
			setCodeValue(newCode.champ.content);
		setTempCodeValue(newCode.champ.content);
		if (champPopover)
			toggleChampChooser();
	};

	const selectChamp = (event, value) => {
		const query = `query getOne($basename: String!) {
			champ(basename: $basename) {
				id
				basename
				content
			}
		}`;
		const variables = { basename: value };
		const api = 'champions';
		if (value)
			fetchGraph(query, variables, api, loadChamp);
	};

	useEffect(() => {
		console.log(`Enter or update CodeEditor.component`);
		if (props.location.state) {
			const query = `query getOne($basename: String!) {
				champ(basename: $basename) {
					id
					basename
					content
				}
			}`;
			const variables = { basename: props.location.state.edit.basename };
			const api = 'champions';
			if (props.location.state.edit.basename)
				fetchGraph(query, variables, api, (newCode) => {
					if (newCode && newCode.champ)
						setCodeValue(newCode.champ.content);
					setTempCodeValue(newCode.champ.content);
					if (champPopover)
						setChampPopover(!champPopover)
				});
		}
	}, [props.location.state, champPopover]);

	return (
		<div className='codeEditorDiv'>
			<h1>Code Editor</h1>
			<CodeMirror
				value={codeValue}
				className='CodeEditor'
				onChange={(editor, metadata, value) => setTempCodeValue(value)}
				options={{
					mode: 'gas',
					theme: 'material',
					lineNumbers: true,
					lineWrapping: true,
					indentWithTabs: true,
					electricChars: true,
					keyMap: keymapArr[keymap]
				}} />
			<div className='btnDiv'>
				<Button
					id='chooseChamp'
					className='btn'
					onClick={toggleChampChooser}>
					<span>Load Champion</span>
				</Button>
				<Button
					id='keymap'
					className='btn'
					onClick={toggleKeymap}>
					<span>{keymapArr[keymap]}</span>
				</Button>
				<Button
					className="btn"
					onClick={toggleSave}>
					<span>Save</span>
				</Button>
			</div>
			<Dialog
				open={champPopover}
				onBackdropClick={toggleChampChooser}>
				<ChampionChooser chooser={selectChamp} />
			</Dialog>
			<Dialog
				open={savePopover}
				onBackdropClick={toggleSave} >
				<SaveChampion content={tempCodeValue} {...props} />
			</Dialog>
		</div>
	);
};

export default CodeEditor;
