#!/bin/bash
if [ $# -eq 2 ]; then
  rm -rf build
  mkdir build
fi
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  rm -rf config
  cp -R configLinux config
else
  rm -rf config
  cp -R configWindows config
fi
cd build
conan install --build=missing ..
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  cmake ..
elif [[ "$OSTYPE" == "cygwin" ]]; then
  cmake -G  "Visual Studio 16 2019" ..
elif [[ "$OSTYPE" == "win32" ]]; then
  cmake -G  "Visual Studio 16 2019" ..
else
  cmake -G  "Visual Studio 16 2019" ..
fi
cmake --build . --config Release -j `nproc`
