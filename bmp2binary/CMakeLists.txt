cmake_minimum_required (VERSION 2.6)
project (bmp2binary)
# ${PROJECT_SOURCE_DIR} the 'PROJECT' can be replaced by the project's exact name
set (HEADER_DIR ${bmp2binary_SOURCE_DIR}/../include)
include_directories (${HEADER_DIR})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable (bmp2binary bmp2binary.cpp ${HEADER_DIR}/bmp2binary.h ${HEADER_DIR}/struct_pixel.h ${HEADER_DIR}/bitmap_image.hpp)