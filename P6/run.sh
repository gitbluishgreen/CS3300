#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/miniRA/

javac P6.java

for file in ./miniRA/*
do
	echo "-----------------------------"
	java P6 <$file >dump.s
        spim -file dump.s >a.txt
	sed -i 1,5d a.txt
	java -jar kgi.jar <$file >b.txt 
	var=$(echo "$file" | cut --delimiter='/' --fields=3)
        cmp -s a.txt b.txt && echo "Test Case $var passed!" || echo "Test Case $var failed!"
done
