#!/usr/bin/env bash

work_dir=$(dirname $0)
cd $work_dir
work_dir=$PWD

cd $work_dir/libmynew 
make $1

cd $work_dir
make $1
