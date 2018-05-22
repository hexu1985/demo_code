#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " in.jpg out.jpg" << endl;
        exit(1);
    }

    cout << CV_VERSION << endl;
    Mat src = imread(argv[1]);
    cvtColor(src, src, CV_BGR2GRAY);
    imwrite(argv[2],src);//保存结果图片

    return 0;
}

