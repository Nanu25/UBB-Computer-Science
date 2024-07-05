#Write a shell script that will read inputs from keyboard until the user writes "stop". For each input, 
#the script will have to do the following:
#-if the input is an existing user (you can use /etc/passwd) it will print the number of processes running for
#that given user (command ps)
#-if the input is a file, it will perform a replace operation as follows: a->@, e->3, i->! and it will
#overwrite the content of the file.
#-if none of them, it will print a proper message on the screen
#At the end, the script will print on the screen what percentage were users, files or none of them.

#!/bin/bash

read word
nr_users=0
nr_files=0
nr_null=0
total=0
while [ $word != "stop" ]
do
	((total+=1))
	user=$(ps -ef | awk '{print $1}' | grep -c -w "$word")
        if [ -f $word ]; then
            file=$(sed -E 's/a/@/g; s/e/3/g; s/i/!/g' "$word" )
            echo "$file"
	    ((nr_files+=1))

        else   if [ $user -ge 1 ]; then
		 echo "$user"
		 ((nr_users+=1))
	        else
			echo "Invalid parameter"
			((nr_null+=1))
		fi
	fi
	read word	
done


echo "User percentage: $((100 * nr_user/total))"
echo "Files percentage: $((100 * nr_files/total))"
echo "Invalid percentage: $((100 * nr_null/total))"
