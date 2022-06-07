#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " in.jpg out.yuv" << endl;
        exit(1);
    }

    cout << CV_VERSION << endl;

    Mat src;
    //需要更改尺寸的图片路径。 
    src=imread(argv[1], 3);
    //完成后结束
    if(!src.data ){  
        cout << "读取图片错误: " << argv[1] << "\n";
        return -1;
    }

    Mat img;
    cvtColor(src, img, COLOR_BGR2YUV_I420);
    unsigned char* pFrame = (unsigned char *) malloc((src.rows)*(src.cols)*3/2);
    if (pFrame == NULL) {
        cout << "malloc pFrame memory error\n";
        return -1;
    }
    memset(pFrame, 0, ((src.rows)*(src.cols)*3/2));
    memcpy(pFrame, img.data, ((src.rows)*(src.cols)*3/2));

    FILE* fp = fopen(argv[2], "wb+");
    if (fp == NULL) {
        cout << "open file error: " << argv[2] << "\n";
        return -1;
    }

    fwrite(pFrame, 1, (src.rows)*(src.cols)*3/2, fp);

    return 0;
}

