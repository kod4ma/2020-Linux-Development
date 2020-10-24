CFLAGS=-Wall -fPIC
GENERATES=prog prog-a prog-so liboutput_static.a liboutput.so
TRASH= *.o file*

all: prog prog-a prog-so

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared -o $@ $^

fun.o:	outlib.h

clean:
	rm -f $(TRASH)

distclean: clean
	rm -f $(GENERATES)

test: test-zero test-one test-three

test-zero: prog prog-a prog-so
	./$< 2>file1 1>/dev/null
	./$<-a 2>file2 1>/dev/null
	LD_LIBRARY_PATH=. ./$<-so 2>file3 1>/dev/null
	cmp --silent file1 file2 || (echo "file1 != file2"; exit 0)
	cmp --silent file1 file3 || (echo "file1 != file3"; exit 0)
	cmp --silent file2 file3 || (echo "file2 != file3"; exit 0)

test-one: prog prog-a prog-so
	./$< arg1 2> file1 1>/dev/null
	./$<-a arg1 2> file2 1>/dev/null
	LD_LIBRARY_PATH=. ./$<-so arg1 2> file3 1>/dev/null
	cmp file1 file2
	cmp file1 file3
	cmp file2 file3

test-three: prog prog-a prog-so
	./$< arg1 arg2 arg3 2> file1 1>/dev/null
	./$<-a arg1 arg2 arg3 2> file2 1>/dev/null
	LD_LIBRARY_PATH=. ./$<-so arg1 arg2 arg3 2> file3 1>/dev/null
	cmp file1 file2
	cmp file1 file3
	cmp file2 file3

