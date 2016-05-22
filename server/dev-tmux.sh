#!/bin/bash

tmux new-session -d 'alarm-clock-dev'
tmux split-window -v 'nodemon -w build build/index.js'
tmux split-window -v 'cd src && ../node_modules/.bin/tsc -w'
tmux split-window -v 'cd web/src && ../../node_modules/.bin/webpack --progress --colors --watch'
tmux -2 attach-session -d
