/**
 * C ����: AVL��
 */

#include "avltree.h"

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
#define ARRAY_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

int main(int argc, char *argv[])
{
    avl_tree_t root = NULL;

    printf("== �߶�: %d\n", avltree_height(root));
    printf("== �������: ");
    for (int i = 0; i < ARRAY_SIZE(arr); i++)
    {
        printf("%d ", arr[i]);
        root = avltree_insert(root, arr[i]);
    }

    printf("\n== ǰ�����: ");
    avltree_traverse_preorder(root);

    printf("\n== �������: ");
    avltree_traverse_inorder(root);

    printf("\n== �������: ");
    avltree_traverse_postorder(root);
    printf("\n");

    printf("== �߶�: %d\n", avltree_height(root));
    printf("== ��Сֵ: %d\n", avltree_minimum(root)->key);
    printf("== ���ֵ: %d\n", avltree_maximum(root)->key);
    printf("== ������ϸ��Ϣ: \n");
    avltree_show(root, root->key, 0);


    int key = 8;
    printf("\n== ɾ�����ڵ�: %d", key);
    root = avltree_delete(root, key);

    printf("\n== �߶�: %d", avltree_height(root));
    printf("\n== �������: ");
    avltree_traverse_inorder(root);
    printf("\n== ������ϸ��Ϣ: \n");
    avltree_show(root, root->key, 0);

    // ���ٶ�����
    avltree_destory(root);
}

