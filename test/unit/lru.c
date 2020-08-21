#include "../../lru.h"
#include <criterion/criterion.h>

Test(lru, init){
    LRUCache cache;
    LRUCache_init(&cache, 2u);

    HashMap map = cache.map;

    cr_assert(map.buckets == NULL);
    cr_assert(map.front == NULL);
    cr_assert(map.rear == NULL);
    cr_assert(map.capacity == 4);
    cr_assert(map.size == 0);
}