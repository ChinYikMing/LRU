#include <stdio.h>
#include <string.h>
#include "lru.h"

int main() {
    LRUCache cache;
    LRUCache_init(&cache, 2u);

    LRUCache_set(&cache, "test");
    LRUCache_set(&cache, "test1");
    LRUCache_set(&cache, "test2");
    LRUCache_set(&cache, "test3");
    LRUCache_set(&cache, "test4");
    LRUCache_set(&cache, "test5");
    LRUCache_set(&cache, "test6");
    LRUCache_set(&cache, "test7");
    LRUCache_set(&cache, "test1");

    LRUCache_get(&cache, "test100");
    LRUCache_get(&cache, "test99");
    LRUCache_get(&cache, "test1010");
    LRUCache_get(&cache, "test10120");
    LRUCache_get(&cache, "test6");
    LRUCache_get(&cache, "test7");
    LRUCache_get(&cache, "test5");
    LRUCache_get(&cache, "test1");

    LRUCache_get_mru(&cache);
    LRUCache_get_lru(&cache);

    LRUCache_destruct(&cache);
    return 0;
}
