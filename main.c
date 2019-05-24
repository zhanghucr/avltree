/**
 * C 语言: AVL树
 */

#include "avltree.h"

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
#define ARRAY_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

int main(int argc, char *argv[])
{
    avl_tree_t root = NULL;

    printf("== 高度: %d\n", avltree_height(root));
    printf("== 依次添加: ");
    for (int i = 0; i < ARRAY_SIZE(arr); i++)
    {
        printf("%d ", arr[i]);
        root = avltree_insert(root, arr[i]);
    }

    printf("\n== 前序遍历: ");
    avltree_traverse_preorder(root);

    printf("\n== 中序遍历: ");
    avltree_traverse_inorder(root);

    printf("\n== 后序遍历: ");
    avltree_traverse_postorder(root);
    printf("\n");

    printf("== 高度: %d\n", avltree_height(root));
    printf("== 最小值: %d\n", avltree_minimum(root)->key);
    printf("== 最大值: %d\n", avltree_maximum(root)->key);
    printf("== 树的详细信息: \n");
    avltree_show(root, root->key, 0);


    int key = 8;
    printf("\n== 删除根节点: %d", key);
    root = avltree_delete(root, key);

    printf("\n== 高度: %d", avltree_height(root));
    printf("\n== 中序遍历: ");
    avltree_traverse_inorder(root);
    printf("\n== 树的详细信息: \n");
    avltree_show(root, root->key, 0);

    // 销毁二叉树
    avltree_destory(root);
}

