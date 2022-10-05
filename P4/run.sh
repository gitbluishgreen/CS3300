#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/miniIR/

javac P4.java

for file in ./miniIR/*
do
	var=$(echo "$file" | cut --delimiter='/' --fields=3)
	var1=$(echo "$var" | cut --delimiter='.' --fields=1)
	java P4 <$file >./output/$var1.microIR
	java -jar pgi.jar <./output/$var1.microIR >a.txt
	java -jar pgi.jar <$file >b.txt
	cmp -s a.txt b.txt && echo "Test Case $var Passed!" || echo "Test Case $var Failed!" 
	echo "-------------------------"
done
