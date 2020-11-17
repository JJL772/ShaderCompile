#!/bin/sh

# Simple script to build dxc
set -e
TOP=$(cd $(dirname $0);pwd)
cd "$TOP/../shared/dxc/"
mkdir build && cd build

cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release $(cat ../utils/cmake-predefined-config-params)

ninja
