cmake_minimum_required(VERSION 3.8)
project(main)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dotgenerator.cpp dotgenerator.h graph.cpp graph.h tester.cpp tester.h ostov.cpp ostov.h)
add_executable(main ${SOURCE_FILES})