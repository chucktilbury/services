#ifndef MEMORY_H
#define MEMORY_H

void* allocMemory(unsigned int size);
void* reallocMemory(void* ptr, unsigned int size);
void freeMemory(void* ptr);
void* copyMemory(void* ptr, unsigned int size);

#define _alloc(s) allocMemory(s)
#define _alloc_ds(t) (t*)allocMemory(sizeof(t))
#define _alloc_ds_array(t, n) (t*)allocMemory(sizeof(t) * (n))
#define _alloc_ds_array_size(t, s, n) (t*)allocMemory((s) * (n))
#define _realloc(p, s) reallocMemory((p), (s))
#define _realloc_ds_array(p, t, n) (t*)reallocMemory((p), sizeof(t) * (n))
#define _realloc_ds_array_size(p, t, s, n) (t*)reallocMemory((p), (s) * (n))
#define _copy_str(s) (char*)copyMemory((void*)s, strlen(s) + 1)
#define _copy_ds(t, p) (t*)copyMemory((void*)(p), sizeof(t))
#define _free(p) freeMemory((void*)p)

#endif