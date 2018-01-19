#include <stdio.h>
#include <stdlib.h>

// 反转二叉树
//
#define STACKCAP 128


typedef struct _node {
    int data;
    struct _node *lchild, *rchild;
} Node, *Tree;

typedef struct _stack {
    Node *stack[STACKCAP];
    int top;
} Stack;


void push(Stack *stack, Node *node) {
    if(stack->top < (STACKCAP-1)) {
        stack->stack[++stack->top] = node;
    }
}

Node *pop(Stack *stack) {
    if(stack->top >= 0) {
        return stack->stack[stack->top--];
    }
    return NULL;
}
