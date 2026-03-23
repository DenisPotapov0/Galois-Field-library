#!/bin/bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
ctest
make coverage
