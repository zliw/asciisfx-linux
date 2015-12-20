AC_INIT([asciisfx], [0.0.1], [asciisfx@wilz.de],
        [asciisfx.tar.gz], [https://github.com/zliw/asciisfx-linux])

AC_PREREQ([2.68])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])
AC_CONFIG_FILES([Makefile])

AC_PROG_CC
AM_PROG_AR
AC_PROG_LIBTOOL

PKG_CHECK_MODULES(ALSA, alsa >= 1.0.0, HAVE_ALSA="yes")
AC_SUBST(ALSA_CFLAGS)
AC_SUBST(ALSA_LIBS)
AC_CHECK_LIB(asound, snd_seq_open, HAVE_ALSA="no")

AC_OUTPUT
