#!/bin/sh -e  

# Ogre is in universe
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe restricted multiverse"
# For clang-3.8
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu/ trusty-updates main universe"

sudo apt-get update -qq

# Here I use --force-yes due to llvm signature errors
sudo apt-get --yes install libogre-1.8-dev libois-dev mercurial \
     libboost-program-options-dev libboost-system-dev libboost-filesystem-dev \
     libboost-graph-dev libboost-test-dev libenet-dev guile-2.0-dev \
     clang-3.8 lldb-3.8 libgtest-dev google-mock 

# Install CEGUI-0 and CEGUI-0-OGRE
hg clone https://bitbucket.org/cegui/cegui cegui-source
cd cegui-source/
hg update -C v0-8
mkdir build
cd build/
cmake ..
make
sudo make install

## Handle linking from /usr/local
sudo echo "/usr/local/lib" >> /etc/ld.so.conf
sudo ldconfig

# build libgtest & libgtest_main
sudo mkdir /usr/src/gtest/build
cd /usr/src/gtest/build
sudo cmake .. -DBUILD_SHARED_LIBS=1
sudo make -j4
sudo ln -s /usr/src/gtest/build/libgtest.so /usr/lib/libgtest.so
sudo ln -s /usr/src/gtest/build/libgtest_main.so /usr/lib/libgtest_main.so
