find /usr/ -maxdepth 3 -name "*i.h" -type f -exec wc -l '{}' \;
#in maxdepth si specifica la profondità a cui ci si deve FERMARE quindi se metto N vengono mostrate le cose fino ad N-1
#cercare in /usr/ i file terminanti in i.h con una profondita massima di 2
#-name per specificare una regex con cui matchare il nome da dare tra apici doppi
#-type per specificare il tipo di file che dobbiamo matchare
#-exec permette di eseguire un comando per ogni file trovato dal find

