#!/bin/sh   

# Ogre isn in universe
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe restricted multiverse"

sudo apt-get update -qq


sudo apt-get install libogre-dev libcegui-mk2-dev libois-dev \
     libboost-program-options-dev libenet-dev guile-2.0-dev
