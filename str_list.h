/*
 * Generic string list.
 */
#ifndef STR_LIST_H
#define STR_LIST_H

#include "ptr_list.h"

typedef PtrList StrList;

#define createStrList() createPtrList()
#define destroyStrList(lst) destroyPtrList((PtrList*)lst)

#define addStrList(lst, ptr) addPtrList((PtrList*)lst, (void*)ptr)
#define getStrList(lst, idx) (const char*)getPtrList((PtrList*)lst, idx)

#define resetStrList(lst) resetPtrList((PtrList*)lst)
#define iterateStrList(lst) (const char*)iteratePtrList((PtrList*)lst)

#endif