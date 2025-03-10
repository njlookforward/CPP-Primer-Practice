cmake_minimum_required(VERSION 3.5.0)
project(ChapterSevenProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterSevenProject ch07_main.cpp Sales_data.cpp Account.cpp)

include(CTest)
enable_testing()

