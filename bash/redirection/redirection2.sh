
./print_test.sh > ./stdout.log
echo $?
cat stdout.log

./print_test.sh > ./stdout.log 2> ./stderr.log
echo $?
cat stdout.log
cat stderr.log

./print_test.sh > ./log.txt 2>&1
echo $?
cat log.txt

./print_test.sh | tee log.txt
echo $?
cat log.txt
