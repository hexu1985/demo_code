ls -1 *.dot | while read file
do
	echo "process $file"
	file_name=${file%.dot}
	dot $file -T png -o ${file_name}.png
done
