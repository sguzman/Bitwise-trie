cmake_minimum_required(VERSION 2.8.4)
project(bitwisetrie)

IF(EXISTS ${/usr/bin/clang})
    set(CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    set(CMAKE_AR      "/usr/bin/llvm-ar")
    #set(CMAKE_LINKER  "/usr/bin/llvm-ld")
    set(CMAKE_NM      "/usr/bin/llvm-nm")
    set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    set(CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
ELSE()
    set(CMAKE_CXX_COMPILER             "/usr/bin/g++")
ENDIF()


set(CMAKE_CXX_FLAGS                "-Wall -std=c++1y -lgtest")
set(CMAKE_CXX_FLAGS_DEBUG          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_VERBOSE_MAKEFILE "FALSE")

set(SOURCE_FILES gtest.cxx)
add_executable(bitwisetrie ${SOURCE_FILES})
