/**
 * AVL树(C语言): C语言实现的AVL树。
 */
 
#include "avltree.h"

int avltree_node_number(avl_tree_t tree)
{
    int    num_l = 0;
    int    num_r = 0;
    
    if (tree == NULL)  //递归出口
    {
        return 0;
    }

    num_l = avltree_node_number(tree->left);
    num_r = avltree_node_number(tree->right);
    return (num_l + num_r + 1);
}

/* 获取叶子节点数量 */
int avltree_leaf_number(avl_tree_t tree)
{
    int    num_l = 0;
    int    num_r = 0;
    
    if (tree == NULL)
    {
        return 0;
    }
    
    if (tree->left == NULL && tree->right == NULL)
    {
        return 1;
    }
    
    num_l = avltree_leaf_number(tree->left);   //左子树中叶节点的个数
    num_r = avltree_leaf_number(tree->right);  //右子树中叶节点的个数
    return (num_l + num_r);
}

/*
 * 获取AVL树的高度
 */
int avltree_height(avl_tree_t tree)
{
    return HEIGHT(tree);
}

/*
 * 前序遍历"AVL树"
 */
void avltree_traverse_preorder(avl_tree_t tree)
{
    if (tree != NULL)
    {
        printf("%d ", tree->key);
        avltree_traverse_preorder(tree->left);
        avltree_traverse_preorder(tree->right);
    }
}

/*
 * 中序遍历"AVL树"
 */
void avltree_traverse_inorder(avl_tree_t tree)
{
    if (tree != NULL)
    {
        avltree_traverse_inorder(tree->left);
        printf("%d ", tree->key);
        avltree_traverse_inorder(tree->right);
    }
}

/*
 * 后序遍历"AVL树"
 */
void avltree_traverse_postorder(avl_tree_t tree)
{
    if (tree != NULL)
    {
        avltree_traverse_postorder(tree->left);
        avltree_traverse_postorder(tree->right);
        printf("%d ", tree->key);
    }
}

/*
 * 查找"AVL树x"中键值为key的节点
 */
#ifdef RECURSIVE_ALGO
avl_node_t* avltree_search(avl_tree_t tree, avl_type_t key)
{
    if (tree == NULL || tree->key == key)
    {
        return tree;
    }

    if (key < tree->key)
    {
        return avltree_search(tree->left, key);
    }
    else
    {
        return avltree_search(tree->right, key);
    }
}
#else
avl_node_t* avltree_search(avl_tree_t tree, avl_type_t key)
{
    while ((tree != NULL) && (tree->key != key))
    {
        if (key < tree->key)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }

    return tree;
}
#endif

/* 
 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
 */
avl_node_t* avltree_minimum(avl_tree_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    while(tree->left != NULL)
    {
        tree = tree->left;
    }
    
    return tree;
}
 
/* 
 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
 */
avl_node_t* avltree_maximum(avl_tree_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    while(tree->right != NULL)
    {
        tree = tree->right;
    }
    
    return tree;
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
static avl_node_t* avltree_rotate_right(avl_tree_t tree)
{
    avl_tree_t sub_left;  /* 旋转后左子树节点变成根节点 */

    sub_left = tree->left;
    tree->left = sub_left->right;
    sub_left->right = tree;

    tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    sub_left->height = MAX(HEIGHT(sub_left->left), tree->height) + 1;

    return sub_left;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
static avl_node_t* avltree_rotate_left(avl_tree_t tree)
{
    avl_tree_t sub_right;  /* 旋转后右子树节点变成根节点 */

    sub_right = tree->right;
    tree->right = sub_right->left;
    sub_right->left = tree;

    tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    sub_right->height = MAX(HEIGHT(sub_right->right), tree->height) + 1;

    return sub_right;
}

/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
static avl_node_t* avltree_rotate_left_right(avl_tree_t tree)
{
    tree->left = avltree_rotate_left(tree->left);

    return avltree_rotate_right(tree);
}

/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
static avl_node_t* avltree_rotate_right_left(avl_tree_t tree)
{
    tree->right = avltree_rotate_right(tree->right);

    return avltree_rotate_left(tree);
}

/*
 * 创建AVL树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     left 是左孩子。
 *     right 是右孩子。
 */
static avl_node_t* avltree_create_node(avl_type_t key, avl_node_t *left, avl_node_t* right)
{
    avl_node_t *p;

    if ((p = (avl_node_t *)malloc(sizeof(avl_node_t))) == NULL)
    {
        return NULL;
    }
    
    p->key = key;
    p->height = 0;
    p->left = left;
    p->right = right;
    return p;
}

/* 
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
avl_node_t* avltree_insert(avl_tree_t tree, avl_type_t key)
{
    if (tree == NULL)
    {
        tree = avltree_create_node(key, NULL, NULL);  // 新建节点
        if (tree == NULL)
        {
            printf("ERROR: avltree_create_node failed.\n");
            return NULL;
        }
    }
    else if (key < tree->key)  // 应该将key插入到"tree的左子树"的情况
    {
        tree->left = avltree_insert(tree->left, key);

        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            if (key < tree->left->key)
            {
                tree = avltree_rotate_right(tree);
            }
            else
            {
                tree = avltree_rotate_left_right(tree);
            }
        }
    }
    else if (key > tree->key)  // 应该将key插入到"tree的右子树"的情况
    {
        tree->right = avltree_insert(tree->right, key);

        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            if (key > tree->right->key)
            {
                tree = avltree_rotate_left(tree);
            }
            else
            {
                tree = avltree_rotate_right_left(tree);
            }
        }
    }
    else //key == tree->key
    {
        printf("ERROR: key is already exist.\n");  // 不允许插入相同key值的节点
    }

    tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    return tree;
}

/* 
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     ptree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
static avl_node_t* avltree_delete_node(avl_tree_t tree, avl_node_t *z)
{
    if (tree == NULL || z == NULL)
    {
        return NULL;
    }

    if (z->key < tree->key)  // 待删除的节点在"tree的左子树"中
    {
        tree->left = avltree_delete_node(tree->left, z);

        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            avl_node_t *r = tree->right;
            if (HEIGHT(r->left) > HEIGHT(r->right))
            {
                tree = avltree_rotate_right_left(tree);
            }
            else
            {
                tree = avltree_rotate_left(tree);
            }
        }
    }
    else if (z->key > tree->key)  // 待删除的节点在"tree的右子树"中
    {
        tree->right = avltree_delete_node(tree->right, z);

        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            avl_node_t *l = tree->left;
            if (HEIGHT(l->right) > HEIGHT(l->left))
            {
                tree = avltree_rotate_left_right(tree);
            }
            else
            {
                tree = avltree_rotate_right(tree);
            }
        }
    }
    else  // tree是对应要删除的节点。
    {
        if (tree->left != NULL && tree->right != NULL)  // tree的左右孩子都非空
        {
            if (HEIGHT(tree->left) > HEIGHT(tree->right))
            {
                // 如果tree的左子树比右子树高；则
                // (01)找出tree的左子树中的最大节点
                // (02)将该最大节点的值赋值给tree。
                // (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                avl_node_t *max = avltree_maximum(tree->left);
                tree->key = max->key;
                tree->left = avltree_delete_node(tree->left, max);
            }
            else
            {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)则
                // (01)找出tree的右子树中的最小节点
                // (02)将该最小节点的值赋值给tree。
                // (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                avl_node_t *min = avltree_minimum(tree->right);
                tree->key = min->key;
                tree->right = avltree_delete_node(tree->right, min);
            }
        }
        else
        {
            avl_node_t *tmp = tree;
            tree = tree->left ? tree->left : tree->right;
            free(tmp);
        }
    }

    return tree;
}

/* 
 * 删除结点(key是节点值)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 待删除的结点的键值
 * 返回值：
 *     根节点
 */
avl_node_t* avltree_delete(avl_tree_t tree, avl_type_t key)
{
    avl_node_t *z; 

    if ((z = avltree_search(tree, key)) != NULL)
    {
        tree = avltree_delete_node(tree, z);
    }
    
    return tree;
}

/* 
 * 销毁AVL树
 */
void avltree_destory(avl_tree_t tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->left != NULL)
    {
        avltree_destory(tree->left);
    }
    
    if (tree->right != NULL)
    {
        avltree_destory(tree->right);
    }

    free(tree);
}

/*
 * 打印"AVL树"
 *
 * tree       -- AVL树的节点
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void avltree_show(avl_tree_t tree, avl_type_t key, int direction)
{
    if (tree != NULL)
    {
        if (direction == DIRECTION_ROOT)    // tree是根节点
        {
            printf("----------------------------------\n");
            printf("tree height: %d\n", avltree_height(tree));
            printf("tree nodes : %d\n", avltree_node_number(tree));
            printf("leaf nodes : %d\n", avltree_leaf_number(tree));
            printf("----------------------------------\n");
            printf("(%2d) root\n", key);
        }
        else if (direction == DIRECTION_RIGHT)
        {
            printf("(%2d) ---> (%2d)\n", key, tree->key);
        }
        else
        {
            printf("(%2d) <--- (%2d)\n", tree->key, key);
        }

        avltree_show(tree->left, tree->key, DIRECTION_LEFT);
        avltree_show(tree->right, tree->key, DIRECTION_RIGHT);
    }
}

