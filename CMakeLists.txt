cmake_minimum_required(VERSION 3.19)
project(fathom)

add_library(fathom src/interpreter.cpp)
target_include_directories(fathom PRIVATE include/fathom)

add_executable(interpret apps/main.cpp)
target_link_libraries(interpret fathom)
target_include_directories(interpret PRIVATE include)
set_target_properties(interpret PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY ".."
	VS_DEBUGGER_COMMAND_ARGUMENTS "test\\hello.bf")
