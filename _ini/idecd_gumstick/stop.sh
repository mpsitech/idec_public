#!/bin/bash
# file stop.sh
# stop script for Idec daemon, release idecd_gumstick
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

pid=$(pgrep Idecd)
kill -15 $pid

