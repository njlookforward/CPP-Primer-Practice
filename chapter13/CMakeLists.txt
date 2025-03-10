cmake_minimum_required(VERSION 3.5.0)
project(ChapterThirteenProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterThirteenProject ch13_main.cpp exercise.cpp Sales_data.cpp HasPtr.cpp strVec.cpp)

include(CTest)
enable_testing()

