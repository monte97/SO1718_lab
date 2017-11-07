#!/bin/bash

while read RIGA; do
	echo ${RIGA%% *} &>2
	echo EVVAI
done;
