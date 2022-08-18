#ifndef MEMORY_H
#define MEMORY_H

void* allocMemory(unsigned int size);
void* reallocMemory(void* ptr, unsigned int size);
void freeMemory(void* ptr);
void* copyMemory(void* ptr, unsigned int size);

#define _alloc(s) allocMemory(s)
#define _alloc_ds(t) (t*)allocMemory(sizeof(t))
#define _alloc_ds_array(t, n) (t*)allocMemory(sizeof(t)*(n))
#define _realloc(p, s) reallocMemory((p), (s))
#define _realloc_ds_array(p, t, n) (t*)reallocMemory((p), sizeof(t)*(n))
#define _copy_str(s) strdup(s) (const char*)copyMemory((const char*)s, strlen(s)+1)
#define _free(p) free((void*)p) freeMemory(p)

#endif