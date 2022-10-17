/*
 * This is a generic string handling library that is loosely based on the
 * Python Way. A string, in this context refers to the String data structure
 * that is defined for this library.
 *
 * Other features may be implemented as required.
 */
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "strings.h"

/*
 * Use strtok() on an allocated buffer.
 *
static inline const char* tokstr(const char* buf, const char* find) {

    static char* tmp;
    if(buf != NULL) {
        tmp = (char*)_copy_str(buf);
        return strtok(tmp, find);
    }
    else
        return strtok(NULL, find);
}
 */

/*
 * Allocate memory for a new String data structure. The parameter can be NULL
 * if an empty string is desired.
 */
String* createStr(const char* buffer) {

    String* sptr = _alloc_ds(String);
    sptr->len = 0;
    sptr->cap = 1;
    sptr->buffer = _alloc_ds_list(char, sptr->cap);

    appendStr(sptr, buffer);

    return sptr;
}

/*
 * Cautiously free a String data structure.
 */
void destroyStr(String* str) {

    if(str != NULL) {
        if(str->buffer != NULL)
            _free(str->buffer);
        _free(str);
    }
}

/*
 * Append the string constant to the string data structure. If there is no
 * string to append, then do nothing.
 */
void appendStr(String* ptr, const char* buffer) {

    if(buffer != NULL) {
        int len = strlen(buffer);
        if(ptr->len + len + 1 > ptr->cap) {
            while(ptr->len + len + 1 > ptr->cap)
                ptr->cap <<= 1;
            ptr->buffer = _realloc_ds_list(ptr->buffer, char, ptr->cap);
        }

        strcat(ptr->buffer, buffer);
        ptr->len += len;
    }
}

/*
 * Prepend a string to the string data structure.
 */
void prependStr(String* ptr, const char* buffer) {

    if(buffer != NULL) {
        int cap = 1;
        char* sptr;
        int tlen = strlen(buffer) + strlen(ptr->buffer) + 1;

        while(tlen > cap)
            cap <<= 1;
        sptr = _alloc(cap);

        strcpy(sptr, buffer);
        strcat(sptr, ptr->buffer);

        _free(ptr->buffer);
        ptr->buffer = sptr;
        ptr->cap = cap;
        ptr->len = tlen;
    }
}

/*
 * Append a formatted string to the String data structure.
 */
void appendStrFmt(String* ptr, const char* fmt, ...) {

    va_list args;
    size_t len;

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* buffer = _alloc(len + 1);
    va_start(args, fmt);
    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);

    appendStr(ptr, buffer);
    _free(buffer);
}

/*
 * Prepend a formatted string the String data structure.
 */
void prependStrFmt(String* ptr, const char* fmt, ...) {

    va_list args;
    size_t len;

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* buffer = _alloc(len + 1);
    va_start(args, fmt);
    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);

    prependStr(ptr, buffer);
    _free(buffer);
}

/*
 * Return a C string from the String data structure.
 */
const char* cStr(String* str) {

    return str->buffer;
}

/*
 * Copy a String data structure, leaving the original unchanged.
 */
String* copyStr(String* str) {

    return createStr(str->buffer);
}

void resetStr(String* s, unsigned char flag) {

    s->index = 0;
    if(flag)
        s->len = 0;
}

/*
 * Replace every instance of the "find" string with the "repl" string in
 * one pass.
 */
String* replaceStr(String* s, const char* find, const char* repl) {

    int finished = 0;
    int state = 0;
    String* retv = createStr(NULL);
    String* tmp = createStr(NULL);
    char* head = s->buffer;
    char* tail = head;
    char* fptr = (char*)find;


    do {
        switch(state) {
            case 0: // simply copy characters
                if(*head == *fptr) {
                    tail = head;
                    state = 1;
                    resetStr(tmp, true);
                }
                else if(*head == '\0') {
                    finished++;
                }
                else {
                    appendChar(retv, *head);
                    head++;
                }
                break;
            case 1: // seen start of find, copy to tmp
                if(*tail == *fptr) {
                    // save the base buffer in tmp
                    appendChar(tmp, *tail);
                    tail++;
                    fptr++;
                }
                else if(*fptr == '\0') {
                    // have a match
                    appendStr(retv, repl);
                    state = 0;
                    fptr = (char*)find;
                    head = tail;
                }
                else if(*tail == '\0') {
                    finished++;
                    appendStr(retv, tmp->buffer);
                }
                else {
                    // not a match, restore tmp and continue
                    appendStr(retv, tmp->buffer);
                    state = 0;
                    fptr = (char*)find;
                    head = tail;
                }
                break;
        }
    } while(!finished);

    return retv;
}

/*
 * Return the index of the next instance of the find string. Returns -1
 * if the string is not found. The index of the string has to be set to
 * zero upon entry.
 */
int findStr(String* buffer, const char* find) {

    int retv = -1;

    char* mark = strstr(&buffer->buffer[buffer->index], find);
    if(mark != NULL) {
        retv = (unsigned long)mark - (unsigned long)buffer->buffer;
        buffer->index += strlen(find);
    }

    return retv;
}

// int rfindStr(String* buffer, const char* find)
// {
// }

/*
 * Find the first instance of a character in a string. Returns the
 * index of the character.
 */
int chrStr(String* buffer, int ch) {

    char* p = strchr(buffer->buffer, ch);
    if(p == NULL)
        return -1;
    else {
        buffer->index = ((unsigned long)p) - ((unsigned long)buffer->buffer);
        return buffer->index;
    }
}

/*
 * Find the last instance of a character in a string. Returns the
 * index of the character.
 */
int rchrStr(String* buffer, int ch) {

    char* p = strrchr(buffer->buffer, ch);
    if(p == NULL)
        return -1;
    else {
        buffer->index = ((unsigned long)p) - ((unsigned long)buffer->buffer);
        return buffer->index;
    }
}

/*
 * Append the string to the base string. Leave the append string intact.
 */
void joinStr(String* base, String* append) {

    appendStr(base, append->buffer);
}

/*
 * Strip the whitespace from the beginning and the end of the string.
 */
void stripStr(String* buffer) {

    char *head, *tail;
    for(head = &buffer->buffer[0]; isspace(*head) && *head != '\0'; head++) { /*nothing*/
    }
    for(tail = head; !isspace(*tail) && *tail != '\0'; tail++) { /*nothing*/
    }
    *tail = '\0';

    tail = _copy_str(head);

    _free(buffer->buffer);
    buffer->buffer = head;
    buffer->len = strlen(buffer->buffer);
    buffer->cap = 1;
    while(buffer->len + 1 > buffer->cap)
        buffer->cap <<= 1;
    buffer->buffer = _realloc_ds_list(buffer->buffer, char, buffer->cap);
}

/*
 * Compare two strings using libc strcmp()
 */
int compareStr(String* left, String* right) {

    return strcmp(left->buffer, right->buffer);
}
