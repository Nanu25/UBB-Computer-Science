 #Să se calculeze și să afișeze numărul de vocale și numărul de consoane dintr-un fișier.

#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1

fi


voc=$(grep -o "[aeiouAEIOU]" "$1" | wc -l)
cons=$(grep -o -i "[^aeiou[:space:][:digit:]]" "$1" | wc -l)

echo "Vowels number $voc"
echo "Cons number $cons"


