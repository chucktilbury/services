#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

typedef enum {
    LIST_OK,
    LIST_EMPTY,
    LIST_CRNT,
    LIST_END,
    LIST_NODE_EMPTY,
    LIST_NODE_SIZE,
    LIST_PARMS,
    LIST_ERROR,
} ListResult;

typedef struct _list_ {
    void* data;
    size_t size;
    struct _list_* prev;
    struct _list_* next;
} ListNode;

typedef struct {
    ListNode* first;
    ListNode* last;
    ListNode* crnt;
    size_t len;
} List;

List* ListCreate();
void ListDestroy(List* ptr);
ListResult listSet(List* ptr, void* data, size_t size);
ListResult listGet(List* ptr, void* data, size_t size);
ListResult listSwap(List* ptr);

ListResult listPrepend(List* ptr, void* data, size_t size);
ListResult listAppend(List* ptr, void* data, size_t size);
ListResult listInsertAfter(List* ptr, void* data, size_t size);
ListResult listInsertBefore(List* ptr, void* data, size_t size);
ListResult listRemove(List* ptr);

ListResult listFirst(List* ptr, void* data, size_t size);
ListResult listLast(List* ptr, void* data, size_t size);
ListResult listNext(List* ptr, void* data, size_t size);
ListResult listPrev(List* ptr, void* data, size_t size);

ListResult listPush(List* ptr, void* data, size_t size);
ListResult listPeek(List* ptr, void* data, size_t size);
ListResult listPop(List* ptr, void* data, size_t size);

#endif