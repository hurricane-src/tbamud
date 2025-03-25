#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint64_t key;
    char *value;
} text_hashmap_node_t;

typedef struct
{
    text_hashmap_node_t *nodes;
    size_t capacity;
    size_t size;
} text_hashmap_t;

typedef enum
{
    text_hashmap_inserted = 0,
    text_hashmap_duplicate = 1,
    text_hashmap_collision = 2,
} text_hashmap_status_t;

typedef struct
{
    text_hashmap_t *map;
    size_t index;
} text_hashmap_iterator_t;

void text_hashmap_init_with_capacity(text_hashmap_t* map, size_t capacity);
void text_hashmap_init(text_hashmap_t* map);
text_hashmap_t* text_hashmap_new();
text_hashmap_status_t text_hashmap_insert_simple(text_hashmap_t *map, uint64_t key, const char *value);
text_hashmap_status_t text_hashmap_insert(text_hashmap_t *map, uint64_t key, const char *value);
text_hashmap_status_t text_hashmap_insert_own_simple(text_hashmap_t *map, uint64_t key, char *value);
text_hashmap_status_t text_hashmap_insert_own(text_hashmap_t *map, uint64_t key, char *value);
char* text_hashmap_get(text_hashmap_t *map, uint64_t key);
char* text_hashmap_remove(text_hashmap_t *map, uint64_t key);
void text_hashmap_deinit(text_hashmap_t *map);
void text_hasmap_delete(text_hashmap_t *map);

void text_hashmap_iterator_init(text_hashmap_iterator_t *iterator, text_hashmap_t *map);
bool text_hashmap_iterator_has_next(text_hashmap_iterator_t *iterator);
const char *text_hashmap_iterator_next(text_hashmap_iterator_t *iterator, uint64_t *key);
