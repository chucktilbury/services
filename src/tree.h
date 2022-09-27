
#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct _node_ {
    const char* key;
    void* data;
    size_t size;
    struct _node_* left;
    struct _node_* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} Tree;

Tree* treeCreate();
void treeDestroy(Tree* tree);
void treeBalance(Tree* tree);
void* treeFind(Tree* tree, const char* key);
void treeAdd(Tree* tree, const char* key, void* data);
void treeRemove(Tree* tree, const char* key);


#endif