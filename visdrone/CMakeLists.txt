# YOLO converters -- helper apps to convert annotations to YOLO format.
# Copyright 2021-2022 Stephane Charette <stephanecharette@gmail.com>
# MIT license applies.  See "license.txt" for details.


ADD_EXECUTABLE (visdrone visdrone.cpp)
TARGET_LINK_LIBRARIES (visdrone Threads::Threads ${OpenCV_LIBS})
