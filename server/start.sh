#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

kill $(ps -Af | grep 'node build/index.js' | awk '{print $2}')
cd ${DIR}
node build/index.js > /tmp/alarm-clock-server.log

