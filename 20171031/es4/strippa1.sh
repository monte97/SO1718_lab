#!/bin/bash

echo "" > "7.txt"
echo "" > "8.txt"
for f in /usr/include/* ; do
	if [[ -f $f ]]; then 
		#echo $f
		f=${f##*/}
		#echo $f
		echo -n ${f:6:1} >> "7.txt" 
		echo -n ${f:7:1} >> "8.txt"
	fi
done
echo "" >> "7.txt"
echo "" >> "8.txt"
