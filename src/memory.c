/*
 * This is a generic memory library that allows garbage collection to be linked in.
 * The preferred GC library can be found here: https://www.hboehm.info/gc/index.html
 * Additional work is needed to interface this. This library simply provides a
 * generic interface to any memory library chosen, include libc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* allocMemory(unsigned int size) {

    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "memory  error: cannot allocate %d bytes\n", size);
        exit(1);
    }

    memset(ptr, 0, size);
    return ptr;
}

void* reallocMemory(void* ptr, unsigned int size) {

    void* nptr = realloc(ptr, size);
    if(nptr == NULL) {
        fprintf(stderr, "memory  error: cannot reallocate %d bytes\n", size);
        exit(1);
    }

    return nptr;
}

void freeMemory(void* ptr) {

    if(ptr != NULL)
        free(ptr);
}

void* copyMemory(void* ptr, unsigned int size) {

    void* nptr = allocMemory(size);
    memcpy(nptr, ptr, size);
    return nptr;
}
