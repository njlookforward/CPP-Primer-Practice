cmake_minimum_required(VERSION 3.5.0)
project(ChapterFourteenProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterFourteenProject ch14_main.cpp exercise.cpp Sales_data.cpp 
               strBlob.cpp strVec.cpp Date.cpp)

include(CTest)
enable_testing()

