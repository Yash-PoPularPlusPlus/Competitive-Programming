for((i = 0; i <= 100; i++)); do 
	echo $i
	./gen $i > input
	java Application < input > output
	./brute < input > output1
	diff -w output output1 || break
done