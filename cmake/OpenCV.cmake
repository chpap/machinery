find_package(OpenCV REQUIRED )
set(OPENCV_LIBRARIES opencv_imgproc opencv_core opencv_highgui opencv_video opencv_videoio opencv_imgcodecs opencv_features2d)
include_directories(${OpenCV_INCLUDE_DIRS})
#link_directories(${OPENCV_LIBRARY_DIR})
