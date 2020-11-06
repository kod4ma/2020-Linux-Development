#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

typedef int (* intvoid)(int, char *, int);

int unlinkat(int fd, char *name, int foo) {
    intvoid _unlinkat;
    if(strstr(name, "FIX")) {
        fprintf(stderr, "not deleting anything that matches *FIX*!\n");
        return EPERM;
    } else {
        _unlinkat = (intvoid)dlsym(RTLD_NEXT, "unlinkat");
        return _unlinkat(AT_FDCWD, name, 0);
    }
}
