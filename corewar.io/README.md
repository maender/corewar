# Corewar.io

## Description
A React/NodeJS app to run the Corewar game online
 - ReactJS
 - NodeJS (>= 8.13.0)
 - GraphQL
 - Firebase
 - Socket.io (TODO)

## First change path locations
 - Open `start.sh` script and change `PROJECT_PATH` variable

```diff
...

+PROJECT_PATH="$HOME/Dev/42/algo/corewar"
COREWARIO="$PROJECT_PATH/corewar.io"
RESOURCES_PATH="$COREWARIO/node/resources"
COREWAR_CHAMPS1=../resources/vm_champs/champs/championships/**/**/*.[s]

...
```

## Copy project and install dependencies
 - `sh start.sh -c`

## Run
 - `sh start.sh`

## Restart running project
 - `sh start.sh -r`

## Access log files
Since `start.sh` is running with the `nohup` command,<br />
 - you can access `node` logs under `$PROJECT_PATH/corewar.io/node/nohup`
 - you can access `react` logs under `$PROJECT_PATH/corewar.io/react/nohup`

## Change Firebase data
The `.env` file is filled with default database for public access.
Please notice that it is a free Firebase account so Quota are really low.<br />
Please change `.env` file with your own firebase project api keys
Find yours under `Firebase Console > Project Settings`

```diff
REACT_APP_DOCKER_HOST=localhost
REACT_APP_DOCKER_NODE_PORT=4000
+ REACT_APP_API_KEY="Your Api key"
+ REACT_APP_AUTH_DOMAIN="Your auth domain"
+ REACT_APP_DATABASE_URL="Your database URL"
+ REACT_APP_PROJECT_ID="Your Project Id"
+ REACT_APP_STORAGE_BUCKET="Your Storage Bucket"
+ REACT_APP_MESSAGING_SENDER_ID="Your Messaging sender Id"
+ REACT_APP_APP_ID="Your App Id"

```

## READMEs
 - [React](react/README.md)

# Author
Edouard Jubert <br/>
edouard.jubert@gmail.com
