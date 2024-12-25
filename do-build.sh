#!/bin/bash

mkdir -p build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cd ..
cmake --build ./build
cd build && ctest --output-on-failure