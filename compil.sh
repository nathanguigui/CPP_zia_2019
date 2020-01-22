#!/bin/bash
if [ $# -eq 2 ]; then
  rm -rf build
  mkdir build
fi
cd build
conan install ..
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  cmake ..
elif [[ "$OSTYPE" == "cygwin" ]]; then
  cmake -G  "Visual Studio 16 2019" ..
elif [[ "$OSTYPE" == "win32" ]]; then
  cmake -G  "Visual Studio 16 2019" ..
else
  cmake -G  "Visual Studio 16 2019" ..
fi
cmake --build . --config Release
