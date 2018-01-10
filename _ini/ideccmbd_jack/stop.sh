#!/bin/bash
# file stop.sh
# stop script for Idec combined daemon, release ideccmbd_jack
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

pid=$(pgrep Ideccmbd)
kill -15 $pid

