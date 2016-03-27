#!/bin/sh
set -e

args=("$@")

# ${args[0]}: repository (e.g., http://github.com/g-truc/gli.git)
# ${args[1]}: directory  (e.g., ${HOME}/extra/gli-git)
# ${args[2]}: branch     (e.g., 0.8.1)

if [ 2 -gt "$#" ]; then
    echo "need at least two args!"
    exit 1
fi

if [ 4 -gt "$#" ]; then
    branch="${args[2]}"
else
    branch="master"
fi

if [ ! -d ${args[1]} ]; then
    echo "creating '${args[1]}'"
    mkdir -p ${args[1]}

    echo "cloning '${args[0]} ${branch}' -> '${args[1]}'"
    git clone -b ${branch} ${args[0]} ${args[1]}
else
    echo "updating '${args[1]}'"
    cd ${args[1]}
    git pull
fi
