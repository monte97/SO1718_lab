#!/bin/bash

for i in `seq 1 10`; do
	./puntini.sh 30 1>&2
	echo "$!"
done
