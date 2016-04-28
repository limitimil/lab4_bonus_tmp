PREFIX=/home/embedded
SOURCE=main.cpp objectDetection.cpp hdmi_show.cpp edgeDetect.cpp findContours_demo.cpp
FLAGS=-g
ALL:
	arm-xilinx-linux-gnueabi-g++ ${FLAGS} -I ${PREFIX}/LAB4/opencv_zed/opencv-2.4.9/install/include  -I ${PREFIX}/LAB4/opencv_zedopencv-2.4.9/install/include/opencv -L ${PREFIX}/LAB4/opencv_zed/opencv-2.4.9/install/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_legacy -lopencv_flann -lpthread ${SOURCE} -o switchcv
sdmv:
	cp switchcv /media/embedded/1CA1-34884/run/switchcv
