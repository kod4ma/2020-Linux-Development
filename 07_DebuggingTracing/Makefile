GENERATES = fake_rm.so *test*

all: fake_rm.so

fake_rm.so: fake_rm.c
	cc --shared -fPIC fake_rm.c -ldl -o fake_rm.so

clean:
	rm -f $(GENERATES)

test:	fake_rm.so
	touch FIXtest1 test1 FIXtest2 test2
	rm FIXtest1 test1
	LD_PRELOAD=`pwd`/fake_rm.so rm FIXtest2 test2 || true
