cmake_minimum_required(VERSION 3.5.0)
project(ChapterTwoProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterTwoProject ch02_main_exercise.cpp Sales_data.cpp)

include(CTest)
enable_testing()

