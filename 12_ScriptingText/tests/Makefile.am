TESTS = test1 test2 test3 test4 test5
check_PROGRAMS = test1 test2 test3 test4 test5
CFLAGS = @CHECK_CFLAGS@ -I../src
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
