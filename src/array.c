
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "memory.h"

#define INDEX(ds, idx) ((idx) * (ds->size))
#define PTR(ds, idx) ((void*)((char*)(&ds->list)[INDEX(ds, idx)]))

Array* arrayCreate(size_t size) {

    Array* val = _alloc_ds(Array);
    val->cap = 1;
    val->len = 0;
    val->index = 0;
    val->size = size;
    val->list = _alloc_ds_array_size(void*, size, val->cap);

    return val;
}

void arrayDestroy(Array* lst) {

    if(lst != NULL) {
        _free(lst->list);
        _free(lst);
    }
}

ArrayResult arrayAdd(Array* lst, void* val) {

    if(lst->len + 1 > lst->cap) {
        lst->cap <<= 1;
        lst->list = _realloc_ds_array_size(lst->list, void*, lst->size, lst->cap);
    }

    memcpy(PTR(lst, lst->len), val, lst->size);
    lst->len++;

    return ARRAY_OK;
}

ArrayResult arrayGet(Array* lst, int idx, void* val) {

    if(idx < 0 || idx >= lst->len)
        return ARRAY_BOUNDS;

    memcpy(val, PTR(lst, idx), lst->size);
    return ARRAY_OK;
}

ArrayResult arraySet(Array* lst, int idx, void* val) {

    if(idx < 0 || idx >= lst->len)
        return ARRAY_BOUNDS;

    memcpy(PTR(lst, idx), val, lst->size);
    return ARRAY_OK;
}

ArrayResult arrayPush(Array* lst, void* val) {

    return arrayAdd(lst, val);
}

ArrayResult arrayPop(Array* lst, void* val) {

    if(lst->len > 0) {
        // memcpy(val, &lst->list[--lst->len], lst->size);
        memcpy(val, PTR(lst, --lst->len), lst->size);
        return ARRAY_OK;
    }
    else
        return ARRAY_BOUNDS;
}

ArrayResult arrayPeek(Array* lst, void* val) {

    if(lst->len > 0) {
        // memcpy(val, &lst->list[lst->len - 1], lst->size);
        memcpy(val, PTR(lst, lst->len - 1), lst->size);
        return ARRAY_OK;
    }
    else
        return ARRAY_BOUNDS;
}

int arrayGetSize(Array* lst) {

    return lst->len;
}

void* arrayGetRaw(Array* lst) {

    return lst->list;
}

#ifdef TEST
/*
 * Build string:
 * clang -Wall -Wextra -g -o t array_examp.c memory.c -DTEST
 */

void dump(Array* arr) {

    printf("cap: %d\n", arr->cap);
    printf("len: %d\n", arr->len);
    for(int i = 0; i < arr->len; i++)
        printf("%3d. %s\n", i + 1, (char*)arr->list[i]);

    printf("\n");
}

int main() {

    const char* strs[] = { "string one",
                           "string two",
                           "string three",
                           "string four",
                           "string five",
                           "string six",
                           "string seven",
                           "string eight",
                           "string nine",
                           "string ten",
                           NULL };

    Array* arr = ArrayCreate(sizeof(char*));

    for(int i = 0; strs[i] != NULL; i++)
        ArrayAdd(arr, (void*)strs[i]);
    dump(arr);

    ArrayDestroy(arr);
    return 0;
}

#endif
