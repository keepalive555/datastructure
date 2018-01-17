#include <stdio.h>
#include <stdlib.h>

#define MAXKEY 512

// LRU算法C语言实现


typedef struct _item {
    char key[MAXKEY];
    void *data; // 指向数据
} Item;


typedef struct _lru_cache {
    // LRU缓存
} LRUCache;

int main(void) {
    return 0;
}
