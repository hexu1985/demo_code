#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " in.jpg out.jpg" << endl;
        exit(1);
    }

    cout << CV_VERSION << endl;

    Mat src;
    //需要更改尺寸的图片路径。 
    src=imread(argv[1]);
    //完成后结束
    if(!src.data ){  
        cout << "读取图片错误: " << argv[1] << "\n";
        return -1;
    }

    Mat img;
    //更改的图片的大小，480是高，640是宽
    resize(src,img,Size(480,640));
    imwrite(argv[2], img);//保存在文件夹中

    return 0;
}

