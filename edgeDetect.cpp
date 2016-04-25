#include "edgeDetect.h"
#include "hdmi_show.h"

using namespace cv;
using namespace std;

Mat image, gray, edge, cedge;


// define a trackbar callback
static void onTrackbar(int, void*)
{
    std::vector<cv::KeyPoint> keypoints;
    cv::FAST( gray, keypoints, 20, true);
    image.copyTo(edge);

    for (int i=0;i<keypoints.size();i++)
    {
      rectangle(edge, cvPoint(keypoints[i].pt.x-1,keypoints[i].pt.y-1),
		cvPoint(keypoints[i].pt.x+1,keypoints[i].pt.y+1), cvScalar(255,0,0),CV_FILLED);
    }

    image.copyTo(cedge, edge);
    imwrite("edge.bmp",edge);
}


static const char* keys =
{
    "{1| |lena.jpg|input image name}"
};

void edgeDetection( int argc, const char** argv )
{
    CommandLineParser parser(argc, argv, keys);
    string filename = parser.get<string>("1");
    image = imread(filename, 1);
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        exit(425);
    }
    cedge.create(image.size(), image.type());
    cvtColor(image, gray, COLOR_BGR2GRAY);
    onTrackbar(0, 0);
    hdmi_show(edge);
}
