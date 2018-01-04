#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MAX_LEVEL 32
#define P 0.25

typedef int KeyType; // 键类型
typedef int ValueType; // 值类型


typedef struct _node {
    KeyType key;
    ValueType value;
    struct _node *forward[1];
} Node;


Node *NIL = NULL;

void init(void) {
    // 初始化NIL节点
    size_t size = sizeof(Node)+MAX_LEVEL*sizeof(Node *);
    NIL = (Node *)malloc(size);
    assert(NIL != NULL);
    memset((void *)NIL, 0, size);
    NIL->key = 0x7fffffff; // int32最大值
}


Node *create_node(int level, KeyType key, ValueType value) {
    // 创建新节点
    size_t size = sizeof(Node) + level*sizeof(Node *);
    Node *node = (Node *)malloc(size);
    if(node == NULL) {
        return NULL;
    }
    memset((void *)node, 0, size);
    int i;
    for(i=0; i<level; i++) {
        // 所有层forward指针均指向NIL节点
        node->forward[i] = NIL;
    }
    node->key = key;
    node->value = value;
    return node;
}

typedef struct _skiplist {
    // 描述跳表的数据结构
    Node *head;
    int level; // 跳表层数
    int len; // 跳表节点数，在O(1)时间复杂度内，获取跳表长度
} SkipList;


int random_level(void) {  
    int level = 1;  
    while ((random() & 0xFFFF) < (P * 0xFFFF))  
        level += 1;  
    return (level < MAX_LEVEL) ? level : MAX_LEVEL;  
}


SkipList* create_skiplist() {
    // 创建新的跳表
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    if(list == NULL) {
        return NULL;
    }
    // 创建头指针
    Node *head = create_node(MAX_LEVEL, 0, 0);
    if(head == NULL) {
        return NULL;
    }
    int i;
    for(i=0; i<MAX_LEVEL; i++) {
        head->forward[i] = NIL;
    }
    list->level = 1; // 初始level=1
    list->head = head;
    list->len = 0;
    return list;
}

Node* find(SkipList *list, KeyType key) {
    // 在跳表list内查找，Key为key的节点
    Node *node = list->head;
    int i;
#ifndef NDEBUG
    int cnt = 0;
#endif
    for(i=list->level-1; i>=0; i--) {
#ifndef NDEBUG
        printf("find level: %d\n", i);
#endif
        while(node->forward[i]->key < key) {
#ifndef NDEBUG
            cnt++;
#endif
            node = node->forward[i];
        }
        if(node->forward[i]->key == key) {
#ifndef NDEBUG
            printf("execute %d times.\n", cnt);
#endif
            return node->forward[i];
        } else if(i == 0) {
            return NULL;
        } else {
            continue;
        }
    }
    return NULL;
}

void insert_node(SkipList *list, KeyType key, ValueType value) {
    // 插入新节点
    Node *node = list->head;
    Node *update[MAX_LEVEL];
    int k;
    for(k=0; k<MAX_LEVEL; k++) {
        update[k] = list->head;
    }
    int i;
    for(i=list->level-1; i>=0; i--) {
        while(node->forward[i]->key < key) {
            node = node->forward[i];
        }
        update[i] = node;
    }
#ifndef NDEBUG
    printf("\n\n");
    printf("=====================insert node start=================\n");
    for(k=0; k<MAX_LEVEL; k++) {
        printf("update node(address=%p, key=%d, value=%d)\n", update[k], update[k]->key, update[k]->value);
    }
    printf("=====================insert node end=================\n");
#endif
    if(node->forward[0]->key == key) {
        // 更改节点值
        node->forward[0]->value = value;
        return;
    }
    // 未找到节点则新建节点并插入
    int level = random_level();
    if (level > list->level) {
        int j;
        for(j=list->level; j<level; j++) {
            update[j] = list->head;
        }
        list->level = level;
    }
    Node *new_node = create_node(level, key, value);
    for(i=0; i<level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    list->len++;
}


void delete(SkipList *list) {
    // 删除key指定的节点
    Node *p = list->head->forward[0];
    Node *q;
    while(p != NULL) {
        q = p->forward[0];
        free((void *)p);
        p = q;
    }
    free((void *)list);
}


void delete_node(SkipList *list, KeyType key) {
    // 从SkipList中删除节点
    Node *node = list->head;
    Node *update[MAX_LEVEL];
    Node *next;
    int i;
    for(i=0; i<MAX_LEVEL; i++) {
        update[i] = list->head;
    }
    for(i=list->level-1; i>=0; i--) {
        while(node->forward[i]->key < key) {
            node = node->forward[i];
        }
        update[i] = node;
    }
    next = node->forward[0];
    if(next->key == key) {
        // 找到该节点，并删除该节点
        for(i=0; i<MAX_LEVEL; i++) {
            if(update[i]->forward[i] == next) {
                update[i]->forward[i] = next->forward[i];
            }
        }
        free((void *)next);
        next = NULL;
        // 修正SkipList level
        while(list->level > 0 \
              && list->head->forward[list->level] == NIL) {
            list->level--;
        }
    }
}

int main() {
    init();
    SkipList *list = create_skiplist();
    int i;
    for(i=1; i<=1000; i++) {
        insert_node(list, i, i);
    }
    printf("skiplist info: level=%d, length=%d\n", list->level, list->len);
    printf("nodes of level 0:\n");
    Node *p = list->head;
    Node *q;
    while((q=p->forward[0]) != NULL) {
        if(q != NIL) {
#ifndef NDEBUG
            printf("node(address=%p, key=%d, vlaue=%d)\n", q, q->key, q->value);
#endif
        }
        p = q;
    }
    Node *node = find(list, 499);
    if(node != NULL) {
        printf("find value: %d\n", node->value);
    }
#ifndef NDEBUG
    printf("delete node!\n");
    delete_node(list, 499);
    printf("delete node sucess!\n");
#endif
    node = find(list, 499);
    if(node != NULL) {
        printf("find value: %d\n", node->value);
    }
    delete(list);
}
