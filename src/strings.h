/*
 * String services.
 */
#ifndef STRINGS_H
#define STRINGS_H

typedef struct {
    char* buffer;
    int cap;
    int len;
    int index;
} String;

String* createStr(const char* str);
void destroyStr(String* str);

void appendStr(String* ptr, const char* str);
void appendChar(String* ptr, int ch);
void prependStr(String* ptr, const char* str);
void appendStrFmt(String* ptr, const char* fmt, ...);
void prependStrFmt(String* ptr, const char* fmt, ...);
const char* cStr(String* str);
String* copyStr(String* str);
String* replaceStr(String* str, const char* find, const char* repl);
int findStr(String* str, const char* find);
int chrStr(String* str, int ch);
int rchrStr(String* str, int ch);
void joinStr(String* base, String* append);
void stripStr(String* str);
int compareStr(String* left, String* right);
void resetStr(String* s, unsigned char flag);

#endif