AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS= -I m4
bin_PROGRAMS = asciisfx
asciisfx_SOURCES = src/main.c
asciisfx_CFLAGS = @SNDFILE_CFLAGS@
asciisfx_LDFLAGS = -lasciisfx -lm @SNDFILE_LIBS@

check_PROGRAMS = tests/test
TESTS = tests/test

tests_test_SOURCES = tests/test.c
tests_test_CFLAGS = -I$(top_srcdir)/src -I/usr/local/include
tests_test_LDFLAGS = -L/usr/local/lib -lasciisfx -lcmocka -lm @SNDFILE_LIBS@

lib_LTLIBRARIES = libasciisfx.la
libasciisfx_la_SOURCES = src/arguments.c src/arguments.h src/buffer.c src/oscillator.c src/parser.c
