#! /bin/sh
set -e

if test -f ccache.tar.gz
then
    tar zxf ccache.tar.gz -C $HOME
fi

mkdir build
cd build

export CMAKE_CXX_COMPILER_LAUNCHER=ccache
/opt/python/cp38-cp38/bin/cmake ..
make VERBOSE=1

cd ..

ccache --show-stats
ccache --show-config

tar zcf ccache.tar.gz -C $HOME .ccache
