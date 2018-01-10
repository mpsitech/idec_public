#!/bin/bash
# file checkout.sh
# checkout script for Idec web-based UI, release webappidec_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set WEBROOT=/home/mpsitech/web

mkdir $WEBROOT/appidec

cp checkin.sh $WEBROOT/appidec/

cp -r ../../webappidec/* $WEBROOT/appidec/

