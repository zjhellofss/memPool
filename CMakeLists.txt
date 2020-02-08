cmake_minimum_required(VERSION 3.15)
project(MemPool)

set(CMAKE_CXX_STANDARD 14)

add_library(MemPool main.cpp memHandler.cpp memHandler.h memPool.cpp memPool.h memBlock.cpp memBlock.h alloc.h alloc.cpp)