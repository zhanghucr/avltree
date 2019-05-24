#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int avl_type_t;

typedef struct avl_tree
{
    avl_type_t key;           // ¹Ø¼ü×Ö(¼üÖµ)
    int height;
    struct avl_tree *left;    // ×óº¢×Ó
    struct avl_tree *right;   // ÓÒº¢×Ó
}avl_node_t, *avl_tree_t;

#define DIRECTION_ROOT         0
#define DIRECTION_LEFT        -1
#define DIRECTION_RIGHT        1
#define HEIGHT(p)              ((p == NULL) ? -1 : (((avl_node_t *)(p))->height))
#define MAX(a, b)              ((a) > (b) ? (a) : (b))

int avltree_height(avl_tree_t tree);
void avltree_traverse_preorder(avl_tree_t tree);
void avltree_traverse_inorder(avl_tree_t tree);
void avltree_traverse_postorder(avl_tree_t tree);
avl_node_t* avltree_search(avl_tree_t tree, avl_type_t key);
avl_node_t* avltree_minimum(avl_tree_t tree);
avl_node_t* avltree_maximum(avl_tree_t tree);
avl_node_t* avltree_insert(avl_tree_t tree, avl_type_t key);
avl_node_t* avltree_delete(avl_tree_t tree, avl_type_t key);
void avltree_destory(avl_tree_t tree);
void avltree_show(avl_tree_t tree, avl_type_t key, int direction);


#endif

