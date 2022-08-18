/*
 * Generic binary tree.
 */
#ifndef TREE_H
#define TREE_H

typedef struct _binary_tree_entry {
    void* key;
    void* data;
    struct _binary_tree_entry* left;
    struct _binary_tree_entry* right;
} BinTreeEntry;

typedef int (*CompFunc)(void* left, void* right);
typedef void (*PrintFunc)(void* data);

typedef struct {
    BinTreeEntry* root;
    CompFunc comp;
    PrintFunc print;
} BinTree;

BinTree* createBinTree(CompFunc comp, PrintFunc print);
void destroyBinTree(BinTree* tree);

void addBinTree(BinTree* bt, void* key, void* data);
void* findBinTree(BinTree* bt, void* key);
void delBinTree(BinTree* bt, void* key);

#endif