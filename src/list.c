
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "memory.h"

#define MIN(l, r) (((l) < (r)) ? (l) : (r))

List* listCreate() {

    List* lst = _alloc_ds(List);
    lst->first = lst->last = lst->crnt = NULL;
    lst->len = 0;

    return lst;
}

void listDestroy(List* ptr) {

    if(ptr != NULL) {
        if(ptr->first != NULL) {
            ListNode *node, *next;
            for(node = ptr->first; node != NULL; node = next) {
                next = node->next;
                if(node->data != NULL)
                    _free(node->data);
                _free(node);
            }
        }
        _free(ptr);
    }
}

ListResult listSet(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    if(ptr->crnt != NULL) {
        if(ptr->crnt->data != NULL) {
            _free(ptr->crnt->data);
        }

        ptr->crnt->data = _alloc(size);
        memcpy(ptr->crnt->data, data, size);
        ptr->crnt->size = size;

        return LIST_OK;
    }
    else
        return LIST_CRNT;
}

ListResult listGet(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    if(ptr->crnt != NULL) {
        if(ptr->crnt->data != NULL) {
            if(ptr->crnt->size != size) {
                memcpy(ptr->crnt->data, data, MIN(ptr->crnt->size, size));
                return LIST_NODE_SIZE;
            }
            else {
                memcpy(ptr->crnt->data, data, size);
                return LIST_OK;
            }
        }
        else
            return LIST_NODE_EMPTY;
    }
    else
        return LIST_CRNT;
}

ListResult listSwap(List* ptr) {

    if(ptr == NULL)
        return LIST_PARMS;

    if(ptr->crnt != NULL && ptr->crnt->next != NULL) {
        ListNode* left = ptr->crnt;
        ListNode* right = ptr->crnt->next;

        if(left->prev != NULL)
            left->prev->next = right;
        if(right->next != NULL)
            right->next->prev = left;

        left->next = right->next;
        right->prev = left->prev;

        left->prev = right;
        right->next = left;

        return LIST_OK;
    }
    else
        return LIST_ERROR;
}

ListResult listPrepend(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    ListNode* node = _alloc_ds(ListNode);
    node->data = _alloc(size);
    memcpy(node->data, data, size);
    node->size = size;
    node->prev = NULL;
    node->next = ptr->first;

    if(ptr->first != NULL)
        ptr->first->prev = node;
    else
        ptr->last = node;
    ptr->crnt = ptr->first = node;

    return LIST_OK;
}

ListResult listAppend(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    ListNode* node = _alloc_ds(ListNode);
    node->data = _alloc(size);
    memcpy(node->data, data, size);
    node->size = size;
    node->next = NULL;
    node->prev = ptr->last;

    if(ptr->last != NULL)
        ptr->last->next = node;
    else
        ptr->first = node;
    ptr->crnt = ptr->last = node;

    return LIST_OK;
}

ListResult listInsertAfter(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    ListNode* node = _alloc_ds(ListNode);
    node->data = _alloc(size);
    memcpy(node->data, data, size);
    node->size = size;
    node->next = node->prev = NULL;

    if(ptr->crnt == NULL)
        return listAppend(ptr, data, size);
    else {
        ListNode* crnt = ptr->crnt;
        node->next = crnt->next;
        if(crnt->next != NULL)
            crnt->next->prev = node;

        node->prev = crnt;
        crnt->next = node;
        ptr->crnt = node;
    }

    return LIST_OK;
}

ListResult listInsertBefore(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    ListNode* node = _alloc_ds(ListNode);
    node->data = _alloc(size);
    memcpy(node->data, data, size);
    node->size = size;
    node->next = node->prev = NULL;

    if(ptr->crnt == NULL)
        return listPrepend(ptr, data, size);
    else {
        ListNode* crnt = ptr->crnt;
        node->prev = crnt->prev;
        if(crnt->prev != NULL)
            crnt->prev->next = node;

        node->next = crnt;
        crnt->prev = node;
        ptr->crnt = node;
    }

    return LIST_OK;
}

ListResult listRemove(List* ptr) {

    if(ptr == NULL)
        return LIST_PARMS;

    ListNode* node = ptr->crnt;

    if(node != NULL) {
        if(node->prev == NULL) {
            ptr->first = node->next;
            ptr->first->prev = NULL;
            if(ptr->first == NULL)
                ptr->crnt = ptr->last = NULL;
            else
                ptr->crnt = ptr->first;
        }
        else if(node->next == NULL) {
            ptr->last = node->prev;
            ptr->last->next = NULL;
            if(ptr->last == NULL)
                ptr->crnt = ptr->first = NULL;
            else
                ptr->crnt = ptr->last;
        }
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            if(node->next != NULL)
                ptr->crnt = node->next;
            else if(node->prev != NULL)
                ptr->crnt = node->prev;
            else
                ptr->crnt = ptr->first;
        }

        if(node->data != NULL)
            _free(node->data);
        _free(node);

        return LIST_OK;
    }
    else
        return LIST_CRNT;
}

ListResult listFirst(List* ptr, void* data, size_t size) {

    if(ptr == NULL)
        return LIST_PARMS;

    if(ptr->first != NULL) {
        ptr->crnt = ptr->first;
        printf("first: %p\n", ptr->first);
        if(data != NULL && ptr->crnt->data != NULL) {
            if(ptr->crnt->size != size) {
                memcpy(data, ptr->crnt->data, MIN(ptr->crnt->size, size));
                return LIST_NODE_SIZE;
            }
            else {
                memcpy(data, ptr->crnt->data, size);
                return LIST_OK;
            }
        }
        else
            return LIST_NODE_EMPTY;
    }
    else {
        ptr->crnt = NULL;
        return LIST_EMPTY;
    }
}

ListResult listLast(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    if(ptr->last != NULL) {
        ptr->crnt = ptr->last;
        printf("last: %p\n", ptr->last);
        if(data != NULL && ptr->crnt->data != NULL) {
            if(ptr->crnt->size != size) {
                memcpy(data, ptr->crnt->data, MIN(ptr->crnt->size, size));
                return LIST_NODE_SIZE;
            }
            else {
                memcpy(data, ptr->crnt->data, size);
                return LIST_OK;
            }
        }
        else
            return LIST_NODE_EMPTY;
    }
    else {
        ptr->crnt = NULL;
        return LIST_EMPTY;
    }
}

ListResult listNext(List* ptr, void* data, size_t size) {

    if(ptr == NULL)
        return LIST_PARMS;

    if(ptr->crnt != NULL) {
        ptr->crnt = ptr->crnt->next;
        printf("next: %p\n", ptr->crnt);
        if(data != NULL && ptr->crnt->data != NULL) {
            if(ptr->crnt->size != size) {
                memcpy(data, ptr->crnt->data, MIN(ptr->crnt->size, size));
                return LIST_NODE_SIZE;
            }
            else {
                memcpy(data, ptr->crnt->data, size);
                return LIST_OK;
            }
        }
        else
            return LIST_NODE_EMPTY;
    }
    else
        return LIST_CRNT;
}

ListResult listPrev(List* ptr, void* data, size_t size) {

    if(ptr == NULL)
        return LIST_PARMS;

    if(ptr->crnt != NULL) {
        ptr->crnt = ptr->crnt->prev;
        printf("prev: %p\n", ptr->crnt);
        if(data != NULL && ptr->crnt->data != NULL) {
            if(ptr->crnt->size != size) {
                memcpy(data, ptr->crnt->data, MIN(ptr->crnt->size, size));
                return LIST_NODE_SIZE;
            }
            else {
                memcpy(data, ptr->crnt->data, size);
                return LIST_OK;
            }
        }
        else
            return LIST_NODE_EMPTY;
    }
    else
        return LIST_CRNT;
}

ListResult listPush(List* ptr, void* data, size_t size) {

    return listAppend(ptr, data, size);
}

ListResult listPeek(List* ptr, void* data, size_t size) {

    if(ptr == NULL || data == NULL || size == 0)
        return LIST_PARMS;

    if(ptr->last != NULL) {
        if(ptr->crnt->size != size) {
            memcpy(data, ptr->crnt->data, MIN(ptr->crnt->size, size));
            return LIST_NODE_SIZE;
        }
        else {
            memcpy(data, ptr->crnt->data, size);
            return LIST_OK;
        }
    }
    else
        return LIST_EMPTY;
}

ListResult listPop(List* ptr, void* data, size_t size) {

    if(ptr == NULL)
        return LIST_PARMS;

    ListResult retv = LIST_OK;

    if(ptr->last != NULL) {
        if(data != NULL && ptr->crnt->data != NULL) {
            if(ptr->crnt->size != size) {
                memcpy(data, ptr->crnt->data, MIN(ptr->crnt->size, size));
                return LIST_NODE_SIZE;
            }
            else {
                memcpy(data, ptr->crnt->data, size);
                return LIST_OK;
            }
        }
        else
            return LIST_OK;

        ListNode* node = ptr->last->prev;
        ptr->last = node;
        if(node->data != NULL)
            _free(node->data);
        _free(node);
        return retv;
    }
    else
        return LIST_EMPTY;
}

#ifdef TEST
// Build string:
// clang -DTEST -Wall -Wextra -g -o t list_template_test.c memory.c
#include <limits.h>

void fdump(List* ptr) {

    int x = 1;

    ListNode* node = ptr->first;
    while(node != NULL) {
        printf("%3d. %ld\tself: %p\tprev: %p\tnext: %p\n", x++,
               node->data ? *(long*)node->data : 0, node, node->prev, node->next);

        node = node->next;
    }

    printf("\n");
}

void rdump(List* ptr) {

    int x = 1;
    ListNode* node = ptr->last;

    while(node != NULL) {
        printf("%3d. %ld\tself: %p\tprev: %p\tnext %p\n", x++,
               node->data ? *(long*)node->data : 0, node, node->prev, node->next);

        node = node->prev;
    }

    printf("\n");
}

int main() {

    List* list = ListCreate();
    long val;

    for(int i = 0; i < 10; i++) {
        val = random();
        ListAppend(list, &val, sizeof(val));
    }

    fdump(list);

    ListFirst(list, NULL, 0);
    for(int i = 0; i < 5; i++)
        ListNext(list, NULL, 0);

    ListRemove(list);

    fdump(list);
    rdump(list);

    ListFirst(list, NULL, 0);
    for(int i = 0; i < 5; i++)
        ListNext(list, NULL, 0);

    val = random();
    ListInsertAfter(list, &val, sizeof(val));
    val = random();
    ListInsertBefore(list, &val, sizeof(val));

    fdump(list);
    rdump(list);

    ListFirst(list, NULL, 0);
    for(int i = 0; i < 5; i++)
        ListNext(list, NULL, 0);
    ListSwap(list);
    fdump(list);


    return 0;
}

#endif
