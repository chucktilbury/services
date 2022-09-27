
/*
 * TODO:
 * - Add compare, print, and allocate functions.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "tree.h"

static void tree_count(TreeNode* node, int* cnt) {

    if(node != NULL) {
        if(node->right != NULL)
            tree_count(node->right, cnt);

        if(node->left != NULL)
            tree_count(node->left, cnt);

        *cnt = *cnt + 1;
    }
}

static TreeNode* tree_find(TreeNode* root, const char* key) {

    int x = strcmp(root->key, key);
    if(x > 0) {
        if(root->right != NULL)
            return tree_find(root->right, key);
        else
            return NULL;
    }
    else if(x < 0) {
        if(root->left != NULL)
            return tree_find(root->left, key);
        else
            return NULL;
    }
    else
        return root;
}

static void tree_add(TreeNode** root, TreeNode* node) {

    if(node != NULL) {
        if(*root == NULL)
            *root = node;
        else if((*(root))->key != NULL) {
            int x = strcmp((*(root))->key, node->key);
            if(x < 0) {
                if((*(root))->left != NULL) {
                    tree_add(&((*(root))->left), node);
                }
                else {
                    (*(root))->left = node;
                }
            }
            else if(x > 0) {
                if((*(root))->right != NULL) {
                    tree_add(&((*(root))->right), node);
                }
                else {
                    (*(root))->right = node;
                }
            }
            else
                printf("duplicate node\n");
        }
    }
}

static void tree_remove(TreeNode* root, TreeNode** node, const char* key) {

    int x = strcmp((*node)->key, key);
    if(x > 0) {
        if((*node)->right != NULL)
            tree_remove(root, &((*node)->right), key);
    }
    else if(x < 0) {
        if((*node)->left != NULL)
            tree_remove(root, &((*node)->left), key);
    }
    else {
        TreeNode *left = (*node)->left, *right = (*node)->right;
        (*node)->left = NULL;
        (*node)->right = NULL;

        _free((*node)->key);
        _free(*node);
        *node = NULL;

        if(right != NULL)
            tree_add(&root, right);
        if(left != NULL)
            tree_add(&root, left);
    }
}

static void tree_destroy(TreeNode* node) {

    if(node->right != NULL)
        tree_destroy(node->right);
    if(node->left)
        tree_destroy(node->left);

    _free(node->key);
    _free(node);
}

static TreeNode* tree_create(const char* key, void* data) {

    TreeNode* node = _alloc_ds(TreeNode);

    node->key = _copy_str(key);
    node->data = data;
    node->left = node->right = NULL;

    return node;
}

void treeBalance(Tree* tree) {

    int left = 0;
    int right = 0;
    tree_count(tree->root->left, &left);
    tree_count(tree->root->right, &right);

    TreeNode* node = tree->root;
    if(left - right > 1) {
        tree->root = node->left;
        node->left = NULL;
        tree_add(&tree->root, node);
        treeBalance(tree);
    }
    else if(right - left > 1) {
        tree->root = node->right;
        node->right = NULL;
        tree_add(&tree->root, node);
        treeBalance(tree);
    }
}

Tree* treeCreate() {

    Tree* tree = _alloc_ds(Tree);
    tree->root = NULL;

    return tree;
}

void treeDestroy(Tree* tree) {

    assert(tree != NULL);

    tree_destroy(tree->root);
}

void* treeFind(Tree* tree, const char* key) {

    assert(tree != NULL);
    assert(key != NULL);

    TreeNode* node = tree_find(tree->root, key);
    if(node != NULL)
        return node->data;
    else {
        printf("node not found!");
        return NULL;
    }
}

void treeAdd(Tree* tree, const char* key, void* data) {

    assert(tree != NULL);
    assert(key != NULL);

    tree_add(&tree->root, tree_create(key, data));
}

void treeRemove(Tree* tree, const char* key) {

    assert(tree != NULL);
    assert(key != NULL);

    if(tree->root != NULL) {
        TreeNode* node = tree->root;
        if(strcmp(node->key, key) == 0) {
            TreeNode* left = node->left;
            TreeNode* right = node->right;
            if(left != NULL) {
                tree->root = left;
                tree_add(&tree->root, right);
            }
            else if(right != NULL) {
                tree->root = right;
                tree_add(&tree->root, left);
            }
            else
                tree->root = NULL;

            _free(node->key);
            _free(node);
        }
        else
            tree_remove(node, &tree->root, key);
    }
}
