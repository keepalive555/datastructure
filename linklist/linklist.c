#include <stdio.h>
#include <stdlib.h>

// 单链表
// 头节点，头指针

typedef int ElementType;

typedef struct _node {
    ElementType data;
    struct _node *next;
} Node, *LinkList;
