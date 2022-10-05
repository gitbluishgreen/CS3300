 varn="jayaku"
 if [ ! -d "~/Documents/CS3300/Bonus/${varn}_expected-output" ] 
 then
	mkdir ${varn}_expected-output
 else
	rm -r ${varn}_expected-output/*
 fi

javac B1.java
for file in ./${varn}_testcases/*.java
do
	var1=$(echo "$file" | cut --fields=3 --delimiter='/')
	var2=$(echo "$var1" | cut --fields=1 --delimiter='.')
	java B1 <$file >./${varn}_expected-output/$var2.ll
done
cd ${varn}_testcases
var=0
for file in *.java
do
	var2=$(echo "$file" | cut --fields=1 --delimiter='.')
 	javac $file
 	java $var2 >a.txt
	clang -w ../${varn}_expected-output/$var2.ll
	./a.out >b.txt
	cmp -s a.txt b.txt && echo "Test Case ${file} passed!" || echo "Test Case ${file} failed!"
 	var=$((var + 1))
done
rm *.class
rm *.txt
cd ..
rm *.class
