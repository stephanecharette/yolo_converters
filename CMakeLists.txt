# YOLO converters -- helper apps to convert annotations to YOLO format.
# Copyright 2021-2024 Stephane Charette <stephanecharette@gmail.com>
# MIT license applies.  See "license.txt" for details.

CMAKE_MINIMUM_REQUIRED (VERSION 3.5)

PROJECT (YoloConverters C CXX)

SET (CMAKE_BUILD_TYPE Release)
SET (CMAKE_CXX_STANDARD 17)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_DEFINITIONS ("-Wall -Wextra -Werror -Wno-unused-parameter")

FIND_PACKAGE (Threads	REQUIRED)
FIND_PACKAGE (OpenCV	REQUIRED)

INCLUDE_DIRECTORIES (${OpenCV_INCLUDE_DIRS})

ADD_SUBDIRECTORY (kaggle)
ADD_SUBDIRECTORY (visdrone)
ADD_SUBDIRECTORY (mscoco)
