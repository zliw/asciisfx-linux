AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS= -I m4
bin_PROGRAMS = asciisfx
asciisfx_SOURCES = src/main.c
asciisfx_LDFLAGS = -lasciisfx

check_PROGRAMS = tests/test
TESTS = test/test

tests_test_SOURCES = tests/test.c
tests_test_CFLAGS = -I$(top_srcdir)/src
tests_test_LDFLAGS = -lasciisfx -lcmocka

lib_LTLIBRARIES = libasciisfx.la
libasciisfx_la_SOURCES = src/arguments.c src/arguments.h
