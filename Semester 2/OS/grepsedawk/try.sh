#!/bin/sh

a=$1
sed 's/[a-z0-9A-Z]//g' $1 | sort | uniq
