#!/bin/bash
set -exuo pipefail
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ $DIR != /opt/MagAOX/source/MagAOX ]]; then
    if [[ ! -e /opt/MagAOX/source/MagAOX ]]; then
        echo "Cloning new copy of MagAOX codebase"
        git clone $DIR /opt/MagAOX/source/MagAOX
    fi
    cd /opt/MagAOX/source/MagAOX
    git remote remove origin
    git remote add origin git@github.com:magao-x/MagAOX.git
    git branch -u origin
    echo "In the future, you can run this script from /opt/MagAOX/source/MagAOX/setup"
else
    echo "Running from clone located at $DIR, nothing to do for cloning step"
fi