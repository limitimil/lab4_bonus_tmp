#ifndef __FINDCONTOURS__H__
#define __FINDCONTOURS__H__
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;
void thresh_callback(int, void*);
int findContours(int,const char**);

#endif

