#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([dumpcurse], [1.0], [jopadan@ctemplar.com])
AC_COPYRIGHT([(C) 2021 Jon Daniel <jopadan@ctemplar.com>])
AC_CONFIG_SRCDIR([print_hex.c])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_MAKE_SET
AM_MAINTAINER_MODE
# Checks for libraries.
AC_CHECK_HEADERS([stdlib.h stdio.h stdint.h string.h error.h errno.h sys/stat.h unistd.h dialog.h])
AC_SEARCH_LIBS([initscr], [ncursesw])
AC_SEARCH_LIBS([new_menu], [menu])
AC_SEARCH_LIBS([_nc_setup_tinfo], [tinfow])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
