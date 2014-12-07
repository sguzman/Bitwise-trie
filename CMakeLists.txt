cmake_minimum_required(VERSION 2.8.4)
project(bitwisetrie)

set(CMAKE_CXX_COMPILER             "/usr/bin/g++")
set(CMAKE_CXX_FLAGS                "-Wall -std=c++1y")
set(CMAKE_CXX_FLAGS_DEBUG          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

#set(CMAKE_AR      "/usr/bin/llvm-ar")
#set(CMAKE_LINKER  "/usr/bin/llvm-link")
#set(CMAKE_NM      "/usr/bin/llvm-nm")
#set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
#set(CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

set(SOURCE_FILES main.cxx)
add_executable(bitwisetrie ${SOURCE_FILES})