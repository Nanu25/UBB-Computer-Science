# Să se afișeze liniile dintr-un fișier în care un cuvânt se repetă de cel puțin 2 ori

#!/bin/bash

if [ $# -le 0 ]; then
	echo "Invalid number of parameters"
	exit 1
fi


for file in $@
do	
	echo "$file"
	
	lines=$(awk '
	{
		delete fr	
		for(i = 1; i <= NF; i++)
	       		fr[$i]++;
	 	for(i = 1; i <= NF; i++) { 
			f(fr[$i] >= 2 && ok==0) {
				print $0; 
				fr[$i] = 0;
				break
			}
		}
	} ' "$file") 
	echo "$lines"
done


