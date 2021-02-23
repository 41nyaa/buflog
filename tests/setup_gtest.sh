#!/bin/sh
#
rm -rf googletest
git clone https://github.com/google/googletest.git
cd googletest
cmake .
make
