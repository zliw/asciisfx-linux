[![Build Status](https://api.travis-ci.org/zliw/asciisfx-linux.svg)](https://api.travis-ci.org/zliw/asciisfx-linux.svg)

# asciisfx-linux

linux-port of asciisfx in c

prerequisites:

cmocha & libtool & alsa development files

e.g. on debian based machines run:

apt-get install libtool libcmocka-dev libasound2-dev

build:

> autoreconf -i
> ./configure
> make
