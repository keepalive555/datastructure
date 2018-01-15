#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _node {
    int data;
    struct _node *next;
} Node, *LinkList;

// 利用快慢指针判断单向链表是否有环儿
int has_cycle(LinkList L) {
    if(!L || !L->next) {
        return 0;
    }
    Node *fast, *slow;
    fast = slow = L;
    // 快指针是否有直接后继
    // 快指针的后继节点是否存在后继
    while(fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if(fast == slow) {
            return 1;
        }
    }
    return 0;
}

void print_linklist(LinkList L) {
    if(!L) {
        return ;
    }
    Node *p = L;
    while(p->next != NULL) {
        printf("node value:%d\n", p->data);
        sleep(1);
        p = p->next;
    }
}

int main(void) {
    int k = 16;
    // 构建带环的单向链表
    Node *t = NULL; // 保存指向尾节点指针
    Node *q = NULL; // 保存指向新节点的指针
    Node *p = NULL; // 保存现有链表的指针
    Node *e = NULL; // 保存环入口点指针
    int i = 0;
    for(i=k-1; i>=0; i--) {
        q = (Node *)malloc(sizeof(Node));
        q->data = i;
        q->next = p;
        p = q;

        if(i==k-1) {
            // 保存尾节点指针
            t = q;
        }
        // 记录环入口点
        if(i==9) {
            e = q;
        }
    }
    LinkList L = p;
    t->next = e; 
    // 输出链表内容
    print_linklist(L);
    printf("has cycle: %d\n", has_cycle(L));
}
