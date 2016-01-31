[![Build Status](https://api.travis-ci.org/zliw/asciisfx-linux.svg)](https://api.travis-ci.org/zliw/asciisfx-linux.svg)

# libasciisfx

c-port of asciisfx

prerequisites:

cmocka & libtool development files

e.g. on debian based machines run:

apt-get install libtool libcmocka-dev libasound2-dev


on Mac OS:

brew install cmocka

build:

> autoreconf -i
> ./configure
> make
