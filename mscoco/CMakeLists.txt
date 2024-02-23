# YOLO converters -- helper apps to convert annotations to YOLO format.
# Copyright 2021-2024 Stephane Charette <stephanecharette@gmail.com>
# MIT license applies.  See "license.txt" for details.


ADD_EXECUTABLE (mscoco2017 mscoco2017.cpp)
TARGET_LINK_LIBRARIES (mscoco2017 Threads::Threads)
