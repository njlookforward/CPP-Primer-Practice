cmake_minimum_required(VERSION 3.5.0)
project(ChapterSixteenProject VERSION 0.1.0 LANGUAGES C CXX)

# add_executable(ChapterSixteenProject ch16_main.cpp TextQuery.cpp QueryResult.cpp Sales_data.cpp)
add_executable(ChapterSixteenProject ch16_main_exercise.cpp)

#set_target_properties(ChapterSixteenProject PROPERTIES
#    VS_DEBUGGER_COMMAND_ARGUMENTS 
#    "\"E:/CPP_Primer_Project/chapter16/out/build/GCConfiguration/ChapterSixteenProject.exe\""
#    "\"E:/CPP_Primer_Project/chapter16/data/absInt\"")

include(CTest)
enable_testing()

