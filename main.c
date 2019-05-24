/**
 * C ÓïÑÔ: AVLÊ÷
 */

#include "avltree.h"

int main(int argc, char *argv[])
{
    avl_tree_t root = NULL;

    if (argc != 2)
    {
        printf("CMD <count>.\n");
        printf("Example.\n");
        printf("CMD 16\n");
        printf("Then input data like 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9\n");
        return -1;
    }

    int count = atoi(argv[1]);
    if (count <= 0)
    {
        printf("count %d error.\n", count);
        return -1;
    }

    int *buff = (int *)malloc(count * sizeof(int));
    if (buff == NULL)
    {
        printf("malloc failed.\n");
        return -1;
    }

    memset(buff, 0, count * sizeof(int));

    printf("== insert elements\n");
    for (int i = 0; i < count; i++)
    {
        printf("data[%d]: ", i);
        scanf("%d", &buff[i]);
        root = avltree_insert(root, buff[i]);
    }

    printf("\n== pre-order: ");
    avltree_traverse_preorder(root);

    printf("\n== mid-order: ");
    avltree_traverse_inorder(root);

    printf("\n== post-order: ");
    avltree_traverse_postorder(root);
    printf("\n");

    printf("== min: %d\n", avltree_minimum(root)->key);
    printf("== max: %d\n", avltree_maximum(root)->key);
    printf("== tree info: \n");
    avltree_show(root, root->key, 0);

    int key = 0;
    printf("\n== delete node key: ");
    scanf("%d", &key);
    root = avltree_delete(root, key);

    printf("\n== mid-order: ");
    avltree_traverse_inorder(root);
    printf("\n== tree info: \n");
    avltree_show(root, root->key, 0);

    avltree_destory(root);
    free(buff);
}

