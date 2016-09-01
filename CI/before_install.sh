#!/bin/sh   

# Ogre isn in universe
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe restricted multiverse"

# Install recent clang release to deal with a C++11/Boost/clang issue
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo add-apt-repository "deb http://apt.llvm.org/precise/ llvm-toolchain-precise-3.9 main"

sudo apt-get update -qq

sudo apt-get install libogre-dev libcegui-mk2-dev libois-dev \
     libboost-program-options-dev libboost-system-dev libboost-filesystem-dev \
     libboost-graph-dev libboost-test-dev libenet-dev guile-2.0-dev clang-3.9
