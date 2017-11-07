#!/bin/bash

./estraiasterischi.sh < input.txt &
echo "fatto"
PID=$! #la var $! contiene il pid dell'ultimo processo lanciato
wait "${PID}" #mette in pausa l'esecuzione finchè il processo con il PID specificato non termina
echo "finito"
