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
    map->empty_idx = 0;

    return 0;
}

int map_set(HashMap *map, char *key){

    // invariant: cache hit
    if(map_get(map, key) != -1)
        return 0;

    // invariant: cache miss
    Entry **buckets = map->buckets;
    size_t idx = map_indexer(map, key);

    Entry *node_new = node_create(key);
    if(!node_new) return -1;

    if(map_isfull(map))
        idx = remove_rear(map);
    else
        idx = map->empty_idx;

    // invariant: the map has empty slot

    buckets[idx] = node_new;
    node_new->idx = idx;
    map->size++;

    // add to front
    if(!map->front){
        map->front = map->rear = node_new;
        return 0;
    }

    map->front->prev = node_new;
    node_new->next = map->front;
    node_new->prev = NULL;
    map->front = node_new;

    return 0;
}

int map_get(HashMap *map, char *key){

    Entry **buckets = map->buckets;
    size_t capacity = map->capacity;
    size_t idx = map_indexer(map, key);

    // the slot is empty
    if(!buckets[idx]){
        map->empty_idx = idx;
        return -1;
    }

    // the buckets[idx] is same as the key
    if(!strcmp(buckets[idx]->key, key)){
        add_to_front(map, buckets[idx]);
        return 0;
    }

    //invariant: collision occur

    for(size_t i = idx + 1; i != idx; i = (i + 1) & (capacity - 1)){

        if(i == capacity)
            i = 0;

        Entry *curr = buckets[i];
        if(!curr){
            map->empty_idx = i;
            return -1;
        }

        if(!strcmp(key, curr->key)){
            add_to_front(map, curr);
            return 0;
        }
    }

    //invariant: key not found

    return -1;
}

int add_to_front(HashMap *map, Entry *node){
    if(!node) return -1;

    if(!map->front) {
        map->front = map->rear = node;
        return 0;
    }

    // the node is at front
    if(!strcmp(map->front->key, node->key))
        return 0;
    else if(!strcmp(map->rear->key, node->key)){
        // the node is at rear
        map->rear = map->rear->prev;
        map->rear->next = NULL;
    } else if(node->prev && node->next){
        // the node is at between
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    map->front->prev = node;
    node->next = map->front;
    node->prev = NULL;
    map->front = node;

    return 0;
}

int remove_rear(HashMap *map){
    if(map->capacity == 1u){
        free(map->front->key);
        free(map->front);
        map->front = map->rear = NULL;
        map->size = 0;
        return 0;
    }

    Entry *rear = map->rear;
    char *rear_key = rear->key;
    size_t idx = rear->idx;
    map->rear = rear->prev;
    map->rear->next = NULL;
    map->size--;
    free(rear_key);
    free(rear);

    return idx;
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
    node_new->idx = 0;

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

    for(size_t i = 0;i < capacity; ++i){
        e = buckets[i];
        if(e){
            free(e->key);
            free(e);
        }
    }

    free(buckets);
    return 0;
}
