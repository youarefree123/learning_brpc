#!/bin/bash

if [ "$1" = "build" ]; then

    # 检查 build 文件夹是否存在
    if [ ! -d "build" ]; then
    # 如果不存在，则创建 build 文件夹
    mkdir build
    echo "The 'build' directory has been created."
    fi

    # 进入 build 文件夹
    cd build || { echo "Failed to enter the 'build' directory"; exit 1; }

    cmake ..
    cmake --build . -j6
    cd ..

elif [ "$1" = "clear" ]; then
    rm -r build
    echo "The 'build' directory has been deleted."
else 
    echo "Usage: $0 build(or clear)"
    exit 1
fi