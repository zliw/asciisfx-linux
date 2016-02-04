[![Build Status](https://api.travis-ci.org/zliw/libasciisfx.svg)](https://api.travis-ci.org/zliw/libasciisfx.svg)

# libasciisfx

c-port of asciisfx as a library

currently produces a commandline tool name asciisfx, which takes an command in the ASCII-SFX DSL (work in progress, less implemented than in swift) and  writes a RIFF wav file to out.wav in the current directory.

##Prerequisites

libsndfile, cmocka & libtool development files

###on Debian based machines run:

apt-get install libtool libcmocka-dev

###on Mac OS X install homebrew and run:

brew install cmocka libsndfile

##Build (for all platforms):

> autoreconf -i
> ./configure
> make


