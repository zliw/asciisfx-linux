[![Build Status](https://api.travis-ci.org/zliw/asciisfx-linux.svg)](https://api.travis-ci.org/zliw/asciisfx-linux.svg)

# libasciisfx

c-port of asciisfx

##Prerequisites

libsndfile, cmocka & libtool development files

###on debian based machines run:

apt-get install libtool libcmocka-dev

###on Mac OS X install homebrew and run:

brew install cmocka libsndfile

##Build (for all platforms):

> autoreconf -i
> ./configure
> make
