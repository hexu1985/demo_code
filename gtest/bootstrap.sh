cd $(dirname $0)
work_dir=$PWD
#echo $work_dir

#git clone https://github.com/google/googletest.git
wget https://github.com/google/googletest/archive/v1.8.x.zip
unzip v1.8.x.zip
cd googletest-1.8.x
mkdir build
cd build
cmake ..
make

cd $work_dir
ln -s googletest-1.8.x/build/googlemock/gtest/ libs
ln -s googletest-1.8.x/googletest/include/ include

