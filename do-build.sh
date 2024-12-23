#!/bin/bash

mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install ..
cd ..
cmake --build ./build
cd build && ctest --output-on-failure