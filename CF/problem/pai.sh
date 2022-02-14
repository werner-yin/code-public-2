fname=CF718D
bname=a
test=50000

g++ $fname.cpp -o $fname -lm -O2
g++ $bname.cpp -o $bname -lm -O2

for i in `seq 1 $test`;
do
	./make $i
	./$fname
	./$bname
	diff $fname.out $bname.out -w
	if [ $? == 0 ];
	then 
		echo Passed test $i.
	else 
		echo Wa on test $i.
		break
	fi
done	
