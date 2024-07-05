#Scrieti un script shell care primeste ca prim argument numele 
#unei extensii de fisier (ex: .txt)
#Scriptul va parcurge recursiv directorul curent si va identifica 
#fisierele cu extensia data ca prim argument, care nu contin niciun 
#numar par si au numar impar de cuvinte.
#Se vor afisa numele acelor fisiere si drepturile de acces 
#(scriere/citire/executie) asupra lor.
#Se va valida numarul argumentelor liniei de comanda. Daca nu exista
# niciun fisier cu extensia data ca prim parametru, se va afisa un 
#mesaj de eroare.


#!/bin/bash

if [ $# -le 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi

extension=$1
shift

if [ ! -d $1 ]; then
	echo "This is not a directory"
	exit 1
fi

nr=0
for file in $(find $1 -name "*$extension")
do
	((nr+=1))
	even=$(grep -c "[02468]" "$file")
	if [ $even -eq 0 ]; then
		words=$(wc -w < "$file")
		if [ $((words % 2)) -eq 1 ]; then
			lines=$(ls -l "$file")
			echo "$lines"
		fi
	else
		echo "The file $file contains even numbers"
	fi	

done	

if [ $nr -eq 0 ]; then
	echo "There aren t such files"
fi
