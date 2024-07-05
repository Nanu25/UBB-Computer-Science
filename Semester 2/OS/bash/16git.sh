#Sa se scrie un script shell care va primi ca argumente oricate nume de fisiere (daca nu s au furnizat se va afisa
#"Nr insuficient de argumente" si isi va incheia executia) Scriptul va citi de la tastatura cuvinte pana se introduce
#stop. Pt fiecare fisier, daca e de tip txt se va afisa numele acestuia, va det si va afisa nr total de linii in care
#cuvantul citit apare. Daca acest nr e par, va adauga ultima linie care contine cuvantul dat la finalul fisierului

#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


read word
lastword=$word
while  [ "$word" != "stop" ]
do
	read word
done

for file in $@
do

	ok=$(grep -c -w  "$lastword" "$file")
	echo "In file $file the word $lastword appears $ok times"
	if [ $((ok%2)) -eq 0 ]; then
		echo "The word $lastword appears even times: $ok"
	fi
done

