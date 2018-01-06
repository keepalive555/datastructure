#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef int ElementType;
typedef int KeyType;

typedef struct _node {
    KeyType key;
    ElementType data;
    struct _node *lchild;
    struct _node *rchild;
} Node, *BSTree;

Node *find_node(BSTree tree, KeyType key) {
    // 非递归方式查找节点
    if(!tree) {
        return NULL;
    }
    Node *parent = tree;
    Node *cur = tree;
    while(cur != NULL) {
        if(key == cur->key) {
            return cur;
        } else if(key < cur->key) {
            cur = cur->lchild;
        } else if(key > cur->key) {
            cur = cur->rchild;
        }
        parent = cur;
    }
    return NULL;
}


void insert_node(BSTree *tree, KeyType key, ElementType data) {
    // 搜索二叉排序树
    Node *cur = *tree;
    Node *parent = NULL;
    while(cur != NULL) {
        parent = cur;
        if(key == cur->key) {
            // 查找到节点，则修改节点
            cur->data = data;
            return ;
        } else if(key < cur->key) {
            // 查找左子树
            cur = cur->lchild;
        } else {
            // 查找右子树
            cur = cur->rchild;
        }
    }
    // 新建节点
    Node *new_node = (Node *)malloc(sizeof(Node));
    if(!new_node) {
        return ;
    }
    new_node->key = key;
    new_node->data = data;
    new_node->lchild = new_node->rchild = NULL;
    // 空树则将新节点直接当做根节点
    if(!parent) {
        *tree = new_node;
    } else if(key < parent->key) {
        parent->lchild = new_node;
    } else {
        parent->rchild = new_node;
    }
    return ;
}


void iter(BSTree tree) {
    // 中序遍历二叉排序树
    if(!tree) {
        return ;
    }
    iter(tree->lchild);
    printf("node====>%d\n", tree->key);
    iter(tree->rchild);
}


void delete_node(BSTree *tree, KeyType key) {
    // 删除节点
    // 如果查找到目标节点，且目标节点为叶子节点，则直接删除节点
    // 如果目标节点仅有左子树或右子树则直接删除，删除节点后需要找到直接前驱与直接后继节点
    if(!*tree) {
        return ;
    }
    Node *cur = *tree;
    Node *parent = NULL;
    Node *prev, *prev_parent = NULL; // 目标节点的直接前驱节点，直接前驱节点的父节点
    Node **p = NULL;
    while(cur != NULL) {
        if(key == cur->key) {
            // 查找到节点
            break;
        } else if(key < cur->key) {
            // 查找左子树
            parent = cur;
            cur = cur->lchild;
            p = &parent->lchild;
        } else {
            // 查找右子树
            parent = cur;
            cur = cur->rchild;
            p = &parent->rchild;
        }
    }
    if(cur) {
        if(!cur->lchild) {
            // 仅有右子树
            *p = cur->rchild;
        } else if(!cur->rchild) {
            // 仅有左子树
            *p = cur->lchild;
        } else {
            // 左右子树均存在，左拐并寻找至右子树最后一个节点。
            prev = cur->lchild;
            while(prev->rchild != NULL) {
                prev_parent = prev;
                prev = prev->rchild;
            }
            if(prev != cur->lchild) {
                prev->lchild = cur->lchild;
            }
            prev->rchild = cur->rchild;
            *p = prev;
            if(!prev_parent) {
                prev_parent->rchild = NULL;
            }
        }
    }
    if(cur) {
        free((void *)cur);
        cur = NULL;
    }
    return ;
}


int main(void) {
    // 输入如果为有序的，则二叉排序树退化为斜树，单链表
    // int a[] = {1, 3, 5, 6, 8, 10, 12, 13};
    int a[] = {8, 12, 1, 3, 4, 5, 6, 10, 9, 13, 15};
    int n = sizeof(a) / sizeof(int);
    BSTree tree = NULL;
    // 构建二叉排序树
    int i;
    for(i=0; i<n; i++) {
        insert_node(&tree, a[i], a[i]);
    }
    // 搜索二叉排序树
    Node *p = find_node(tree, 8);
#ifndef NDEBUG
    printf("pointer of p: %p\n", p);
#endif
    if(p) {
        printf("find node vlaue: %d\n", p->data);
    }
    // iter(tree);
    delete_node(&tree, 8);
    iter(tree);
    p = find_node(tree, 8);
#ifndef NDEBUG
    printf("pointer of p: %p\n", p);
#endif
    if(p) {
        printf("find node vlaue: %d\n", p->data);
    }
}
