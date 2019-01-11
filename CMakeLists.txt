cmake_minimum_required(VERSION 2.8)

PROJECT( cubicBezierCurve )

# Make sure the compiler can find include files from our library. 
include_directories (/usr/local/include/opencv2) 
include_directories (/usr/local/include) 
#include_directories ( ${OpenCV_INCLUDE_DIRS} ) 

FIND_PACKAGE( OpenCV REQUIRED )

ADD_LIBRARY( bezier bezier.cpp ) 
ADD_EXECUTABLE( main main.cpp )

TARGET_LINK_LIBRARIES( main bezier )
TARGET_LINK_LIBRARIES( main ${OpenCV_LIBS} )
