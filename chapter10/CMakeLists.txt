cmake_minimum_required(VERSION 3.5.0)
project(ChapterTenProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterTenProject ch10_main.cpp exercise.cpp)

include(CTest)
enable_testing()

