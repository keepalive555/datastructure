#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define BIG_CONSTANT(x) (x##LLU)

// 移位
#define SHIFT 0x05

// 掩码
#define MASK 0xffffffff

// 释放动态内存
#define SAFE_FREE(ptr) do{ \
    if (ptr != NULL) { \
        free((void *)ptr); \
        ptr = NULL; \
    } \
}while(0)

// murmur2哈希函数
uint64_t murmurhash(const void * key, int len, uint64_t seed);

// 哈希函数Proto
typedef uint64_t (*hashfunc)(const void*, int, uint64_t);

// 布隆过滤器
typedef struct __bloomfilter {
    // 哈希函数
    hashfunc hash;
    // 哈希函数随机数种子
    uint64_t *seeds;
    // 哈希函数个数
    int hash_count;
    // 位数组
    uint32_t *bits;
    // 位数组容量（即：数组比特数）
    uint64_t cap;
    // 位数组元素个数
    uint64_t size;
} bloomfilter_t;

// 置位方法
void set(bloomfilter_t * bloomfilter, const void *key, int len) {
    assert(bloomfilter != NULL);
    int i;
    for(i=0; i<bloomfilter->hash_count; i++) {
        uint64_t hashcode = bloomfilter->hash(key, len, bloomfilter->seeds[i]);
        uint64_t n = hashcode % bloomfilter->cap;
        bloomfilter->bits[n >> SHIFT] |= 1 << (n & MASK);
    }
}

// 测试否置位
int test(bloomfilter_t *bloomfilter, void *key, int len) {
    assert(bloomfilter != NULL);
    int ok = 1;
    int i;
    for(i=0; i<bloomfilter->hash_count; i++) {
        uint64_t hashcode = bloomfilter->hash(key, len, bloomfilter->seeds[i]);
        uint64_t n = hashcode % bloomfilter->cap;
        uint64_t idx = n >> SHIFT;
        if (!(bloomfilter->bits[idx] & (1 << (n & MASK)))) {
            ok = 0;
        }
    }
    return ok;
}

// 创建布隆过滤器
bloomfilter_t *create_bloomfilter(uint64_t cap, uint64_t size, int hash_count) {
    bloomfilter_t *bloomfilter = (bloomfilter_t *)malloc(sizeof(bloomfilter_t));
    if (bloomfilter == NULL) {
        return NULL;
    }
    // 初始化哈希相关
    bloomfilter->hash_count = hash_count;
    bloomfilter->hash = murmurhash;
    bloomfilter->seeds = (uint64_t *)malloc(sizeof(uint64_t)*hash_count);
    if (bloomfilter->seeds == NULL) {
        SAFE_FREE(bloomfilter);
        return NULL;
    }
    int i;
    // 哈希函数加盐所需seed采用数组元素指针（确保唯一）
    for(i=0; i<bloomfilter->hash_count; i++) {
        bloomfilter->seeds[i] = (uint64_t)&bloomfilter->seeds[i] & 0x00000000ffffffff;
    }
    // 初始化bits
    bloomfilter->cap = cap;
    bloomfilter->size = size;
    int bytes = cap / sizeof(uint32_t) * sizeof(uint32_t) + 1;
    bloomfilter->bits = (uint32_t *)malloc(bytes);
    if (bloomfilter->bits == NULL) {
        SAFE_FREE(bloomfilter->seeds);
        SAFE_FREE(bloomfilter);
    }
    memset((void *)bloomfilter->bits, 0, bytes);
    return bloomfilter;
}

// 销毁布隆过滤器
void destroy_bloomfilter(bloomfilter_t *bloomfilter) {
    if (bloomfilter != NULL) {
        if (bloomfilter->seeds != NULL) {
            SAFE_FREE(bloomfilter->seeds);
        }
        if (bloomfilter->bits != NULL) {
            SAFE_FREE(bloomfilter->bits);
        }
        SAFE_FREE(bloomfilter);
    }
}

// Murmurhash264A
// @Reference: https://github.com/aappleby/smhasher/blob/master/src/MurmurHash2.cpp
uint64_t murmurhash(const void * key, int len, uint64_t seed)
{
  const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
  const int r = 47;

  uint64_t h = seed ^ (len * m);

  const uint64_t * data = (const uint64_t *)key;
  const uint64_t * end = data + (len/8);

  while(data != end)
  {
    uint64_t k = *data++;

    k *= m; 

    k ^= k >> r; 
    k *= m; 
    
    h ^= k;
    h *= m; 
  }

  const unsigned char * data2 = (const unsigned char*)data;

  switch(len & 7)
  {
  case 7: h ^= (uint64_t)data2[6] << 48;
  case 6: h ^= (uint64_t)data2[5] << 40;
  case 5: h ^= (uint64_t)data2[4] << 32;
  case 4: h ^= (uint64_t)data2[3] << 24;
  case 3: h ^= (uint64_t)data2[2] << 16;
  case 2: h ^= (uint64_t)data2[1] << 8;
  case 1: h ^= (uint64_t)data2[0];
          h *= m;
  };
 
  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
}

int main(int argc, char **argv) {
    bloomfilter_t *bloomfilter = create_bloomfilter(1500, 500, 3);
    // 批量设置数据
    int i;
    for(i=1; i<1000; i+=2) {
        set(bloomfilter, (void *)&i, sizeof(int));
    }
    // 检测是否全部命中布隆过滤器
    int ok;
    for(i=1; i<1000; i++) {
        ok = test(bloomfilter, (void *)&i, sizeof(int));
        printf("%d\n", ok);
    }
    destroy_bloomfilter(bloomfilter);
    return 0;
}

