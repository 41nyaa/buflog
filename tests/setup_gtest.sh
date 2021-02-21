#!/bin/sh
#
rm -rf googltest
git clone https://github.com/google/googletest.git
cd googletest
cmake .
make
