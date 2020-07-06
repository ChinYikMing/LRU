#ifndef LRU_HASHMAP_H
#define LRU_HASHMAP_H

#include <stddef.h>

typedef struct entry Entry;
struct entry {
    Entry *prev;
    Entry *next;
    char *key;
};

typedef struct map {
    Entry **buckets;
    Entry *front;
    Entry *rear;
    size_t capacity;
    size_t size;
} HashMap;

size_t hash33(char *key);

size_t map_indexer(HashMap *map, char *key);

int map_init(HashMap *map, size_t cap_bits);

int map_get(HashMap *map, char *key);

int map_isfull(HashMap *map);

Entry *node_create(char *key);

int add_to_front(HashMap *map, Entry *node);

int remove_rear(HashMap *map);

int map_destruct(HashMap *map);

#endif //LRU_HASHMAP_H
