#include "lru.h"

int LRUCache_init(LRUCache *cache, size_t cap_bits){
    return map_init(&cache->map, cap_bits) < 0 ? -1 : 0;
}

int LRUCache_set(LRUCache *cache, char *key){
    return map_set(&cache->map, key);
}

void LRUCache_get(LRUCache *cache, char *key){
    int ret = map_get(&cache->map, key);

    if(ret == -1)
        printf("%s not found in cache\n", key);
    else
        printf("%s is in the cache\n", key);
}

int LRUCache_get_mru(LRUCache *cache){
    printf("Most recently used is %s\n", cache->map.front->key);

    return 0;
}

int LRUCache_get_lru(LRUCache *cache){
    printf("Least recently used is %s\n", cache->map.rear->key);

    return 0;
}

int LRUCache_destruct(LRUCache *cache){
    map_destruct(&cache->map);

    return 0;
}
