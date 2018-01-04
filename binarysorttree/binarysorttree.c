#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 二叉排序树

typedef int ElementType;
typedef int KeyType;

typedef struct _node {
    KeyType key;
    ElementType data;
    struct _node *lchild;
    struct _node *rchild;
} Node, *BSTree;


int find_node_r(BSTree tree, KeyType key, Node *parent, Node **p) {
    // 递归方式遍历搜索二叉排序树
    // FIXME: 特殊情况不需要遍历的
    if(!tree) {
        // 空树
        *p = parent;
        return -1;
    } else if(key == tree->key) {
        // 查找成功
        *p = tree;
        return 0;
    } else if(key < tree->key) {
        // 搜索左子树
        return find_node_r(tree->lchild, key, tree, p);
    } else {
        // 搜索右子树
        return find_node_r(tree->rchild, key, tree, p);
    }
}


Node *find_node(BSTree tree, KeyType key) {
    // 已非递归方式遍历二叉排序树
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


void insert_node(Node *tree, KeyType key, ElementType data) {
    return ;
}
