cmake_minimum_required(VERSION 3.5.0)
project(QueryProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(QueryProject Query.cpp QueryResult.cpp testQuery.cpp TextQuery.cpp)

include(CTest)
enable_testing()

