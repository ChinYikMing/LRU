#include "lru.h"

int LRUCache_init(LRUCache *cache, size_t cap_bits){
    int ret = map_init(&cache->map, cap_bits);
    if(ret < 0)
        return -1;

    return 0;
}

int LRUCache_get(LRUCache *cache, char *key){
    map_get(&cache->map, key);

    printf("The most used is %s\n", cache->map.front->key);
    return 0;
}

int LRUCache_destruct(LRUCache *cache){
    map_destruct(&cache->map);

    return 0;
}
