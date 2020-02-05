#!/bin/bash
if [ $# -eq 2 ]; then
  rm -rf build
  mkdir build
fi
cd build
conan install --build=missing ..
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  rm -rf config
  cp -R configLinux config
  cmake ..
elif [[ "$OSTYPE" == "cygwin" ]]; then
  rm -rf config
  cp -R configWindows config
  cmake -G  "Visual Studio 16 2019" ..
elif [[ "$OSTYPE" == "win32" ]]; then
  rm -rf config
  cp -R configWindows config
  cmake -G  "Visual Studio 16 2019" ..
else
  rm -rf config
  cp -R configWindows config
  cmake -G  "Visual Studio 16 2019" ..
fi
cmake --build . --config Release
