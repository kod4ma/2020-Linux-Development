#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Growable Memory Buffers for C99], [0.0.0], [gentalionrus@gmail.com])
AM_INIT_AUTOMAKE([foreign])
PKG_CHECK_MODULES([CHECK],[check])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/buf.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT


date=$(date)
str=$(echo AC_PACKAGE_NAME \(AC_PACKAGE_VERSION\) :   "$date")

for file in $(ls -1 */{*.c,*.h})
do
 	echo "=== $file ==="
 	sed -i "1{/^\/\* COMMENT:: .*\*\//d;}" $file
 	sed -n "1{/^\/\* COMMENT:: .*\*\//p;}" $file
 	sed -i "1s/^/\/\* COMMENT:: $str\*\/\n/" $file
 	

done

echo "/* COMMENT::" $str  "*/"