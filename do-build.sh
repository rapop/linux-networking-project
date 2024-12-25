#!/bin/bash

# build & test serializer
cd serializer
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../../install ..
# make
# make install
cmake --build . --target install
# cmake --install .
ctest --output-on-failure
cd ../..

# build networking
cd networking
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../../install -DCMAKE_PREFIX_PATH=../../install ..
cmake --build . --target install
cd ../..

# build notifier-app
cd notifier-app
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../../install -DCMAKE_PREFIX_PATH=../../install ..
cmake --build .
cd ../..