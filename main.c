#include <stdio.h>
#include <string.h>
#include "lru.h"

#define BUF_SIZE 0x0400

int main() {
    LRUCache cache;
    LRUCache_init(&cache, 2u);
    

    char buf[BUF_SIZE];
    while(fgets(buf, BUF_SIZE, stdin)){
        buf[strcspn(buf, "\r\n")] = '\0';

        LRUCache_get(&cache, buf);
    }

    Entry *rear = cache.map.rear;
    if(rear)
        printf("The LRU is %s\n", rear->key);

    LRUCache_destruct(&cache);
    return 0;
}
