#!/bin/bash

ELENCO=`ls`
LungNameDirectory=0
for name in $ELENCO; do
	if [ -d ${name} ]; then
		((LungNameDirectory=$LungNameDirectory+${#name}))
	else
		echo ${name}
	fi
done
echo ${LungNameDirectory}
