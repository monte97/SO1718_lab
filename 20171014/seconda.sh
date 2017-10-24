#!/bin/bash

while read P S O; do
	OUT=${OUT}${S}
done <$1
echo ${OUT}
