cmake_minimum_required(VERSION 3.5.0)
project(ChapterFifteenProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterFifteenProject ch15_main_exercise.cpp QueryResult.cpp TextQuery.cpp
               Quote.cpp )

include(CTest)
enable_testing()

