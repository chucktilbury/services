
/*
 * TODO:
 * - Add compare, print, and allocate functions.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MIN(l, r) (((l) < (r)) ? (l) : (r))
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

static TreeErr tree_add(TreeNode** root, TreeNode* node) {

    if(node != NULL) {
        if(*root == NULL) {
            *root = node;
            return TREE_OK;
        }
        else if((*(root))->key != NULL) {
            int x = strcmp((*(root))->key, node->key);
            if(x < 0) {
                if((*(root))->left != NULL) {
                    tree_add(&((*(root))->left), node);
                }
                else {
                    (*(root))->left = node;
                    return TREE_OK;
                }
            }
            else if(x > 0) {
                if((*(root))->right != NULL) {
                    tree_add(&((*(root))->right), node);
                }
                else {
                    (*(root))->right = node;
                    return TREE_OK;
                }
            }
            else
                return TREE_DUPLICATE;
        }
    }

    return TREE_ERR;
}

static TreeErr tree_remove(TreeNode* root, TreeNode** node, const char* key) {

    int x = strcmp((*node)->key, key);
    if(x > 0) {
        if((*node)->right != NULL)
            return tree_remove(root, &((*node)->right), key);
    }
    else if(x < 0) {
        if((*node)->left != NULL)
            return tree_remove(root, &((*node)->left), key);
    }
    else {
        TreeNode *left = (*node)->left, *right = (*node)->right;
        (*node)->left = NULL;
        (*node)->right = NULL;

        _free((*node)->key);
        _free((*node)->data);
        _free(*node);
        *node = NULL;

        if(right != NULL)
            tree_add(&root, right);
        if(left != NULL)
            tree_add(&root, left);

        return TREE_OK;
    }

    return TREE_ERR;
}

static TreeErr tree_destroy(TreeNode* node) {

    if(node->right != NULL)
        tree_destroy(node->right);
    if(node->left)
        tree_destroy(node->left);

    _free(node->key);
    _free(node->data);
    _free(node);

    return TREE_OK;
}

static TreeNode* tree_create(const char* key, void* data, size_t size) {

    TreeNode* node = _alloc_ds(TreeNode);

    node->key = _copy_str(key);
    node->data = _alloc(size);
    node->size = size;
    memcpy(node->data, data, size);
    node->left = node->right = NULL;

    return node;
}

TreeErr treeBalance(Tree* tree) {

    int left = 0;
    int right = 0;
    tree_count(tree->root->left, &left);
    tree_count(tree->root->right, &right);

    TreeNode* node = tree->root;
    if(left - right > 1) {
        tree->root = node->left;
        node->left = NULL;
        tree_add(&tree->root, node);
        return treeBalance(tree);
    }
    else if(right - left > 1) {
        tree->root = node->right;
        node->right = NULL;
        tree_add(&tree->root, node);
        return treeBalance(tree);
    }

    return TREE_OK;
}

Tree* treeCreate() {

    Tree* tree = _alloc_ds(Tree);
    tree->root = NULL;

    return tree;
}

TreeErr treeDestroy(Tree* tree) {

    if(tree == NULL)
        return TREE_PARAM;

    return tree_destroy(tree->root);
}

TreeErr treeFind(Tree* tree, const char* key, void* data, size_t size) {

    if((tree == NULL) || (key == NULL))
        return TREE_PARAM;

    TreeNode* node = tree_find(tree->root, key);
    if(node != NULL) {
        memcpy(data, node->data, MIN(size, node->size));
        if(size != node->size)
            return TREE_SIZE;
        else
            return TREE_OK;
    }
    else {
        return TREE_NOT_FOUND;
    }

    return TREE_ERR;
}

TreeErr treeAdd(Tree* tree, const char* key, void* data, size_t size) {

    if((tree == NULL) || (key == NULL))
        return TREE_PARAM;

    return tree_add(&tree->root, tree_create(key, data, size));
}

TreeErr treeRemove(Tree* tree, const char* key) {

    if((tree == NULL) || (key == NULL))
        return TREE_PARAM;

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
            _free(node->data);
            _free(node);

            return TREE_OK;
        }
        else
            return tree_remove(node, &tree->root, key);
    }

    return TREE_ERR;
}
