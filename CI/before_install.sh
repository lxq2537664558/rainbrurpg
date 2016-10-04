#!/bin/sh   

# Ogre is in universe
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe restricted multiverse"
# For clang-3.8
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu/ trusty-updates main universe"

# Install recent clang release to deal with a C++11/Boost/clang issue
 #       sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
 #   sudo add-apt-repository "deb http://apt.llvm.org/precise/ llvm-toolchain-precise-3.8 main"
 #   wget -O - http://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
 #   sudo apt-get --yes --force-yes clang-3.8 lldb-3.8 

sudo apt-get update -qq

# Here I use --force-yes due to llvm signature errors
sudo apt-get --yes install libogre-1.8-dev libcegui-mk2-dev libois-dev \
     libboost-program-options-dev libboost-system-dev libboost-filesystem-dev \
     libboost-graph-dev libboost-test-dev libenet-dev guile-2.0-dev \
     clang-3.8 lldb-3.8 libgtest-dev google-mock

# build libgtest & libgtest_main
sudo mkdir /usr/src/gtest/build
cd /usr/src/gtest/build
sudo cmake .. -DBUILD_SHARED_LIBS=1
sudo make -j4
sudo ln -s /usr/src/gtest/build/libgtest.so /usr/lib/libgtest.so
sudo ln -s /usr/src/gtest/build/libgtest_main.so /usr/lib/libgtest_main.so
