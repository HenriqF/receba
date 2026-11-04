#ifndef HASH
#define HASH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct HashItem{
    char* key;
    int value;

    struct HashItem* next;
} HashItem;

typedef struct HashMap{
    size_t buckets;
    size_t pairs;
    HashItem* HashItems;
} HashMap;



void init_hashmap(HashMap* HashMap);

void set_key(HashMap* HashMap, char* key, int value);
void remove_key(HashMap* HashMap, char* key);
int get_value(HashMap HashMap, char* key);

#endif