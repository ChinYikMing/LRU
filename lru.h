#ifndef LRU_LRU_H
#define LRU_LRU_H

#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

typedef  struct lru_cache {
    HashMap map;
} LRUCache;

int LRUCache_init(LRUCache *cache, size_t cap_bits);

int LRUCache_set(LRUCache *cache, char *key);

void LRUCache_get(LRUCache *cache, char *key);

int LRUCache_get_mru(LRUCache *cache);

int LRUCache_get_lru(LRUCache *cache);

int LRUCache_destruct(LRUCache *cache);

#endif //LRU_LRU_H
