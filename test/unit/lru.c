#include "../../lru.h"
#include <criterion/criterion.h>

Test(lru, init){
    LRUCache cache;
    LRUCache_init(&cache, 2u);
    HashMap *map = &cache.map;

    cr_assert(map->buckets != NULL);
    cr_assert(map->front == NULL);
    cr_assert(map->rear == NULL);
    cr_assert(map->capacity == 4);
    cr_assert(map->size == 0);

    LRUCache_destruct(&cache);
}

Test(lru, set){
    LRUCache cache; 
    LRUCache_init(&cache, 2u);
    HashMap *map = &cache.map;

    LRUCache_set(&cache, "test 1");
    LRUCache_set(&cache, "test 2");
    LRUCache_set(&cache, "test 3");
    LRUCache_set(&cache, "test 4");
    LRUCache_set(&cache, "test 5");

    cr_expect_str_eq(map->front->key, "test 5", "expected 'test 5' is most recently used entry");
    cr_expect_str_eq(map->rear->key, "test 2", "expected 'test 2' is least recently used entry");

    LRUCache_destruct(&cache);
}

Test(lru, get){
    LRUCache cache; 
    LRUCache_init(&cache, 2u);
    HashMap *map = &cache.map;
    int ret;

    LRUCache_set(&cache, "test 1");
    LRUCache_set(&cache, "test 2");
    LRUCache_set(&cache, "test 3");
    LRUCache_set(&cache, "test 4");
    LRUCache_set(&cache, "test 5");

    ret = LRUCache_get(&cache, "test 3");

    cr_expect_str_eq(map->front->key, "test 3", "expected 'test 3' is most recently used entry");
    cr_expect_str_eq(map->rear->key, "test 2", "expected 'test 2' is least recently used entry");
    cr_assert(ret == 0);

    ret = LRUCache_get(&cache, "test 2");

    cr_expect_str_eq(map->front->key, "test 2", "expected 'test 2' is most recently used entry");
    cr_expect_str_eq(map->rear->key, "test 4", "expected 'test 4' is least recently used entry");
    cr_assert(ret == 0);

    ret = LRUCache_get(&cache, "test 100");
    cr_assert(ret == -1);

    LRUCache_destruct(&cache);
}
