#!/bin/bash

sleep 2
TUTTO=""
while read RIGA; do #read ha come exit status il numero di caratteri letti, 0 se non legge. while termina con input = 0
	while [[ "${RIGA}" != "" ]]; do
		PAROLA="${RIGA%% *}" #voglio eliminare la sequenza più lunga formata da uno spazio seguito da un qualunque numero di caratteri
		echo "${PAROLA}"
		if echo "${PAROLA}" | grep -q "*" ;then #grep ha come exit status 0 se trova un match nel suo input
			TUTTO="${TUTTO} ${PAROLA}"
		fi
		#se la parola include un * la devo aggiungere ad una variabile
		if [[ "${RIGA}" = "${PAROLA}"  ]];then
			RIGA=""
		else
			RIGA="${RIGA#* }"
		fi
	done
	echo ""
done
echo "${TUTTO}"
