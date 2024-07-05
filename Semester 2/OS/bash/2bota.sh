#2. Să se determine și să afișeze linia dintr-un fișier care conține cele mai multe caractere.

#!/bin/bash


if [ $# -ne 1 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


if [ ! -f $1 ]; then
	echo "This is not a file"
	exit 1
fi


line=$(awk 'length > maxlen {maxlen = length; line = $0} END{print line}' $1)
echo "$line"
		

