#!/bin/bash

mkdir -p build
cd build
cmake ..
cd ..
cmake --build ./build
cd build && ctest --output-on-failure