#!/bin/bash
# file checkin.sh
# checkin script for Idec web-based UI, release webappidec_gumstick
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set REPROOT=/home/mpsitech/srcrep

cp -r * $REPROOT/idec/webappidec/

rm $REPROOT/idec/webappidec/checkin.sh

