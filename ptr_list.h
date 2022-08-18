/*
 * Generic pointer list with iteration.
 */
#ifndef PTR_LIST_H
#define PTR_LIST_H

typedef struct {
    void** list;
    int cap;
    int len;
    int index;
} PtrList;

PtrList* createPtrList();
void destroyPtrList(PtrList* lst);

void addPtrList(PtrList* lst, void* ptr);
void* getPtrList(PtrList* lst, int idx);

void resetPtrList(PtrList* lst);
void* iteratePtrList(PtrList* lst);

void pushPtrList(PtrList* lst, void* ptr);
void* popPtrList(PtrList* lst);
void* peekPtrList(PtrList* lst);

#endif