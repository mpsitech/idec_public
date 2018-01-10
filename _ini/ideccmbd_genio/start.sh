#!/bin/bash
# file start.sh
# start script for Idec combined daemon, release ideccmbd_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

nohup ./Ideccmbd -nocp &
disown

