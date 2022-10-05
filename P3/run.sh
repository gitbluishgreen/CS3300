#!/bin/bash

#Uncomment this the first time you run it:-

#wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" https://www.cse.iitm.ac.in/~krishna/cs3300/minijava/
javac  P3.java

for file in ./minijava/*.java
do
	echo "-----------------"
	var=$(echo "$file" | cut --delimiter='/' --fields=3)
	exec=$(echo "$var" | cut --delimiter='.' --fields=1)
	java P3 <$file >./output/$exec.miniIR 
	java -jar pgi.jar <./output/$exec.miniIR  >$exec.txt
	echo "Done processing $var" 
done
cd minijava
for file in *.java
do
	exec=$(echo "$file" | cut --delimiter='.' --fields=1)
	javac $file
	java $exec >a.txt
	cmp -s a.txt ../$exec.txt  && echo "Test Case $file Passed!" || echo "Test Case $file Failed!"
done
rm *.class
rm *.txt
cd ..
rm *.class
rm *.txt
