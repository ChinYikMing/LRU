#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map_init(HashMap *map, size_t cap_bits){
    size_t cap = 1u << cap_bits;
    if(!(map->buckets = calloc(cap, sizeof(Entry *))))
        return -1;

    map->capacity = cap;
    map->size = 0;
    map->front = map->rear = NULL;

    return 0;
}

int map_get(HashMap *map, char *key){

    Entry **buckets = map->buckets;
    size_t capacity = map->capacity;

    size_t idx = map_indexer(map, key);
    if(!buckets[idx]){
        Entry *node_new = node_create(key);
        buckets[idx] = node_new;
        map->size++;
        add_to_front(map, node_new);

        return 0;
    }

    //invariant: the buckets[idx] has item

    if(!strcmp(key, buckets[idx]->key)){
        add_to_front(map, buckets[idx]);
        return 0;
    }

    //invariant: collision occur

    for(size_t i = idx + 1; i != idx; i = (i + 1) & (capacity - 1)){
       if(i == capacity)
           i = 0;

       Entry *curr = buckets[i];
       if(i < capacity && !curr){
           idx = i;
           break;
       }

       if(i < capacity && !strcmp(key, curr->key)){
           add_to_front(map, curr);
           return 0;
       }
    }

    //invariant: key not found

    if(map_isfull(map))
        idx = remove_rear(map);

    //invariant: the map has empty slot

    Entry *node_new = node_create(key);
    if(!node_new)
        return -1;

    buckets[idx] = node_new;
    map->size++;
    add_to_front(map, node_new);

    return 0;
}

int add_to_front(HashMap *map, Entry *node){
    if(!node) return -1;

    if(!map->front) {
        map->front = node;

        if(!map->rear)
            map->rear = map->front;
        return 0;
    }

    if(!strcmp(map->front->key, node->key))
        return 0;

    if(!node->next){
        if(node->prev)
            node->prev->next = NULL;
    } else if(node->prev && node->next){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    map->front->prev = node;
    node->next = map->front;
    map->front = node;

    return 0;
}

int remove_rear(HashMap *map){
    char *key = map->rear->key;
    map->rear = map->rear->prev;
    map->rear->next = NULL;
    map->size--;

    Entry **buckets = map->buckets;
    size_t capacity = map->capacity;
    size_t idx = map_indexer(map, key);
    Entry *e = buckets[idx];

    if(!strcmp(e->key, key)){
        free(e->key);
        free(e);

        return idx;
    }

    for(size_t i = idx + 1; i != idx; i = (i + 1) & (capacity - 1)){
        if(i == capacity)
            i = 0;

        e = buckets[i];
        if(e && !strcmp(e->key, key)){
            free(e->key);
            free(e);

            return i;
        }
    }

    return -1;
}

Entry *node_create(char *key){
    Entry *node_new = malloc(sizeof(Entry));
    if(!node_new) return NULL;
    node_new->key = strdup(key);
    if(!node_new->key){
        free(node_new);
        return NULL;
    }
    node_new->prev = node_new->next = NULL;

    return node_new;
}

size_t hash33(char *key){
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

size_t map_indexer(HashMap *map, char *key){
    size_t hval = hash33(key);

    return hval & (map->capacity - 1);
}

int map_isfull(HashMap *map){
    return (map->size == map->capacity);
}

int map_destruct(HashMap *map){
    size_t capacity = map->capacity;
    Entry **buckets = map->buckets;
    Entry *e;
    for(size_t i = 0;i < map->capacity; ++i){
        e = buckets[i];
        if(e){
            free(e->key);
            free(e);
        }
    }

    free(buckets);
    return 0;
}
