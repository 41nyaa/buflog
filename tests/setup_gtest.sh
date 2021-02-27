#!/bin/sh
#
rm -rf googletest
git clone https://github.com/google/googletest.git googletest
cmake -S ./googletest -B ./googletest
make -C googletest
