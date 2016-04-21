#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include "hdmi_show.h"

/** Function Headers */
void detectAndDisplay( Mat frame );
void objectDetection( int argc,const char** argv );

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame );
