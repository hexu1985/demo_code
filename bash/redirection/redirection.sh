
./print_test > ./stdout.log
echo $?
cat stdout.log

./print_test > ./stdout.log 2> ./stderr.log
echo $?
cat stdout.log
cat stderr.log

./print_test > ./log.txt 2>&1
echo $?
cat log.txt

./print_test | tee log.txt
echo $?
cat log.txt
