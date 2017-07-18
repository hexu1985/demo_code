#!/bin/sh
# usage: cvs_add_recur.sh dir/file
# 递归遍历dir执行, cvs add

DEBUG=0

# cvs add file
add_file() {
	(( $DEBUG )) && echo "add file $1"
	cvs add $1
	cvs commit -m "" $1
	echo "cvs add $1"
}

# cvs add dir, 递归的
add_dir() {
	(( $DEBUG )) && echo "add dir $1"
	local curr_path
	curr_path=$1
	curr_path=${curr_path%/}
	(( $DEBUG )) && echo "curr_path $curr_path"
	add_file $curr_path
	ls -1 $curr_path | \
	while read file
	do
		(( $DEBUG )) && echo "line $file"
		if [[ -f $curr_path/$file ]]
		then
			add_file $curr_path/$file
		elif [[ -d $curr_path/$file ]] && [[ "$file" != "CVS" ]]
		then
			add_dir $curr_path/$file
		fi
	done
}

if (( $# != 1 ))
then
	echo "usage: $(basename $0) dir|file"
	exit 1
fi

add_path=$1

if [[ -f $add_path ]]
then
	(( $DEBUG )) && echo "$1 is an file"
	add_file $add_path
elif [[ -d $add_path ]]
then
	(( $DEBUG )) && echo "$1 is an directory"
	add_dir $add_path
else
	(( $DEBUG )) && echo "$1 is other type"
	echo "$add_path is not file/dir"
	exit 1
fi
