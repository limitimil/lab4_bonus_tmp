#ifndef __HEDGEDETECT__H__
#define __HEDGEDETECT__H__
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cstdlib>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/videodev2.h>
using namespace cv;


// define a trackbar callback
static void onTrackbar(int, void*);
void edgeDetection( int argc, const char** argv );
#endif
