#include <stdio.h>
#include <string.h>
#include "lru.h"

#define BUF_SIZE 0x0400

int main() {
    LRUCache cache;
    LRUCache_init(&cache, 2u);
    Entry *rear = cache.map->rear;

    char buf[BUF_SIZE];
    while(fgets(buf, BUF_SIZE, stdin)){
        buf[strcspn(buf, "\r\n")] = '\0';

        LRUCache_get(&cache, buf);
    }

    if(rear)
        printf("The LRU is %s\n", rear->key);

    LRUCache_destruct(&cache);
    return 0;
}
