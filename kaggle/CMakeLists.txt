# YOLO converters -- helper apps to convert annotations to YOLO format.
# Copyright 2021-2022 Stephane Charette <stephanecharette@gmail.com>
# MIT license applies.  See "license.txt" for details.


ADD_EXECUTABLE (kaggle kaggle.cpp)
TARGET_LINK_LIBRARIES (kaggle Threads::Threads)

