#!/bin/bash
# file start.sh
# start script for Idec daemon, release idecd_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

nohup ./Idecd -nocp &
disown

