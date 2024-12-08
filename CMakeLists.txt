cmake_minimum_required(VERSION 2.8.12)

project(learning_brpc LANGUAGES C CXX)

add_subdirectory(brpc)

# 设置头文件目录
set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/brpc/output")
set(INCLUDE_PATH "${OUTPUT_PATH}/include")
set(LIB_PATH "${OUTPUT_PATH}/lib") 

add_subdirectory(example)