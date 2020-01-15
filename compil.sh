#!/bin/bash
mkdir build
cd build
conan install ..
cmake -G  "Visual Studio 16 2019" ..
cmake --build . --config Release