#!/bin/bash

NUM=0
while ((${RANDOM}%10 != 2)); do
	((NUM=$NUM+1))	
done
echo ${NUM}
