cmake_minimum_required(VERSION 3.5.0)
project(ChapterTwelveProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterTwelveProject ch12_main.cpp exercise.cpp strBlob.cpp TextQuery.cpp QueryResult.cpp)

include(CTest)
enable_testing()

