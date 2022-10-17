
#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef enum {
    TREE_OK,
    TREE_ERR,
    TREE_NOT_FOUND,
    TREE_DUPLICATE,
    TREE_SIZE,
    TREE_PARAM,
} TreeErr;

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
TreeErr treeDestroy(Tree* tree);
TreeErr treeBalance(Tree* tree);
TreeErr treeFind(Tree* tree, const char* key, void* data, size_t size);
TreeErr treeAdd(Tree* tree, const char* key, void* data, size_t size);
TreeErr treeRemove(Tree* tree, const char* key);


#endif
