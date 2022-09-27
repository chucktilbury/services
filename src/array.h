
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdlib.h>

typedef enum {
    ARRAY_OK,
    ARRAY_END,
    ARRAY_BOUNDS,
    ARRAY_ERROR,
} ArrayResult;

typedef struct {
    void* list;
    size_t size;
    int cap;
    int len;
    int index;
} Array;

Array* arrayCreate(size_t size);
void arrayDestroy(Array* lst);
ArrayResult arrayAdd(Array* lst, void* val);
ArrayResult arrayGet(Array* lst, int idx, void* val);
ArrayResult arraySet(Array* lst, int idx, void* val);
ArrayResult arrayPush(Array* lst, void* val);
ArrayResult arrayPop(Array* lst, void* val);
ArrayResult arrayPeek(Array* lst, void* val);
int arrayGetSize(Array* lst);
void* arrayGetRaw(Array* lst);


#endif