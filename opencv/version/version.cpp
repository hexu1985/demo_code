#include "opencv2/opencv.hpp"
 
using namespace cv;
using namespace std;
 
int main( int argc, char** argv )
{
  cout << "OpenCV version : " << CV_VERSION << endl;
  cout << "Major version : " << CV_MAJOR_VERSION << endl;
  cout << "Minor version : " << CV_MINOR_VERSION << endl;
  cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

#if CV_MAJOR_VERSION == 3
  cout << "this is opencv 3" << endl;
#elif CV_MAJOR_VERSION == 2
  cout << "this is opencv 2" << endl;
#else
  cout << "this is opencv " << CV_MAJOR_VERSION << endl;
#endif
 
  if ( CV_MAJOR_VERSION < 3)
  {
      // Old OpenCV 2 code goes here. 
  } else
  {
      // New OpenCV 3 code goes here. 
  }

  return 0;
}
