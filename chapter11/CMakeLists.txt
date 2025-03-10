cmake_minimum_required(VERSION 3.5.0)
project(ChapterElevenProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterElevenProject ch11_main_exercise.cpp exercise.cpp Sales_data.cpp)
 
include(CTest)
enable_testing()

