RIGA='1 * 2'
RIGA="${RIGA}"
#echo "${RIGA}" #chiedre al prof perchè quotare
while [[ "${RIGA}" != " " ]]; do
	PAROLA=${RIGA%% *}
	echo "${PAROLA}"
	#fino a qui
	#non funziona perchè non è in grado di eliminare l'ultimo carattere dato che non matca con "* "
	#vista la mancanza dello spazio
	#devo verificare se la parola attuale conincide con la riga, in quel caso ho finito perchè
	#ho appena stampato l'ultimo carattere
	if [[ "${PAROLA}" == "${RIGA}" ]];then #controllo se è l'ultimo carattere
		RIGA=" " #se lo è setto riga per fare fallire il controllo al ciclo successivo
	else	#se non lo è aggiorno riga e vaffanculo
		RIGA="${RIGA#* }" # '#' significa elimina la più corta substring che matcha il pattern
	fi
done
