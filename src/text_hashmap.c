#include "text_hashmap.h"

#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

static uint64_t hash_function(uint64_t key, size_t capacity)
{
    return key % capacity;
}

size_t text_hashmap_next_size(size_t current_size)
{
    static const size_t prime_sizes[] =
    {
        17, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191,
        16381, 32749, 65521, 131071, 262139, 524287, 1048573,
        2097143, 4194301, 8388593, 16777213
    };

    static const size_t num_sizes = sizeof(prime_sizes) / sizeof(prime_sizes[0]);

    for(size_t i = 0; i < num_sizes; i++)
    {
        if(prime_sizes[i] > current_size)
        {
            return prime_sizes[i];
        }
    }

    //return prime_sizes[num_sizes - 1]; // Return the largest available if exceeded
    abort();
}

void text_hashmap_init_with_capacity(text_hashmap_t* map, size_t capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->nodes = calloc(map->capacity, sizeof(text_hashmap_node_t));
}

void text_hashmap_init(text_hashmap_t* map)
{
    text_hashmap_init_with_capacity(map, INITIAL_CAPACITY);
}

static inline bool text_hashmap_node_used(const text_hashmap_node_t *node)
{
    return node->value != NULL;
}

text_hashmap_t* text_hashmap_new()
{
    text_hashmap_t *map = malloc(sizeof(text_hashmap_t));
    text_hashmap_init(map);
    return map;
}

static void text_hashmap_resize(text_hashmap_t *map);

text_hashmap_status_t text_hashmap_insert_simple(text_hashmap_t *map, uint64_t key, const char *value)
{
    if ((double)map->size / map->capacity >= LOAD_FACTOR)
    {
        text_hashmap_resize(map);
    }

    size_t index = hash_function(key, map->capacity);

    while(text_hashmap_node_used(&map->nodes[index]))
    {
        if(map->nodes[index].key == key)
        {
            // check if the value is already the same
            if(strcmp(map->nodes[index].value, value) == 0)
            {
                return text_hashmap_duplicate;
            }
            // there is a collision
            return text_hashmap_collision;
        }
        index = (index + 1) % map->capacity;
    }

    map->nodes[index].key = key;
    map->nodes[index].value = strdup(value);
    map->size++;
    return text_hashmap_inserted;
}

text_hashmap_status_t text_hashmap_insert(text_hashmap_t *map, uint64_t key, const char *value)
{
    text_hashmap_status_t ret;
    while((ret = text_hashmap_insert_simple(map, key, value)) == text_hashmap_collision)
    {
        text_hashmap_resize(map);
    }
    return ret;
}

text_hashmap_status_t text_hashmap_insert_own_simple(text_hashmap_t *map, uint64_t key, char *value)
{
    if ((double)map->size / map->capacity >= LOAD_FACTOR)
    {
        text_hashmap_resize(map);
    }

    size_t index = hash_function(key, map->capacity);

    while(text_hashmap_node_used(&map->nodes[index]))
    {
        if(map->nodes[index].key == key)
        {
            // check if the value is already the same
            if(strcmp(map->nodes[index].value, value) == 0)
            {
                return text_hashmap_duplicate;
            }
            // there is a collision
            return text_hashmap_collision;
        }
        index = (index + 1) % map->capacity;
    }

    map->nodes[index].key = key;
    map->nodes[index].value = value;
    map->size++;
    return text_hashmap_inserted;
}

text_hashmap_status_t text_hashmap_insert_own(text_hashmap_t *map, uint64_t key, char *value)
{
    text_hashmap_status_t ret;
    while((ret = text_hashmap_insert_own_simple(map, key, value)) == text_hashmap_collision)
    {
        text_hashmap_resize(map);
    }
    return ret;
}

char* text_hashmap_get(text_hashmap_t *map, uint64_t key)
{
    size_t index = hash_function(key, map->capacity);
    while(text_hashmap_node_used(&map->nodes[index]))
    {
        if(map->nodes[index].key == key)
        {
            return map->nodes[index].value;
        }
        index = (index + 1) % map->capacity;
    }
    return NULL;
}

char* text_hashmap_remove(text_hashmap_t *map, uint64_t key)
{
    size_t index = hash_function(key, map->capacity);
    while(text_hashmap_node_used(&map->nodes[index]))
    {
        if(map->nodes[index].key == key)
        {
            char *text = map->nodes[index].value;
            free(map->nodes[index].value);
            map->nodes[index].key = 0;
            map->nodes[index].value = NULL;
            map->size--;
            return text;
        }
        index = (index + 1) % map->capacity;
    }
    return NULL;
}

static void text_hashmap_resize(text_hashmap_t *map)
{
    text_hashmap_t next_map;
    size_t new_capacity = map->capacity * 2;
    bool failed = false;
    for(;;)
    {
        text_hashmap_init_with_capacity(&next_map, new_capacity);

        for(size_t i = 0; i < map->capacity; i++)
        {
            if(text_hashmap_node_used(&map->nodes[i]))
            {
                if(text_hashmap_insert_simple(&next_map, map->nodes[i].key, map->nodes[i].value) == text_hashmap_collision)
                {
                    // failed
                    free(next_map.nodes);
                    new_capacity = new_capacity * 2;
                    failed = true;
                    break;
                }
            }
        }

        if(failed)
        {
            failed = false;
            continue;
        }

        // all the nodes have been inserted
        free(map->nodes);
        map->nodes = next_map.nodes;
        map->capacity = new_capacity;
        return;
    }
}

void text_hashmap_deinit(text_hashmap_t *map)
{
    for (size_t i = 0; i < map->capacity; i++)
    {
        if(text_hashmap_node_used(&map->nodes[i]))
        {
            free(map->nodes[i].value);
        }
    }
    free(map->nodes);
}

void text_hasmap_delete(text_hashmap_t *map)
{
    text_hashmap_deinit(map);
    free(map);
}

void text_hashmap_iterator_init(text_hashmap_iterator_t *iterator, text_hashmap_t *map)
{
    iterator->map = map;
    iterator->index = 0;
}

bool text_hashmap_iterator_has_next(text_hashmap_iterator_t *iterator)
{
    for(size_t i = iterator->index; i < iterator->map->capacity; i++)
    {
        if(iterator->map->nodes[i].value != NULL)
        {
            iterator->index = i;
            return true;
        }
    }
    return false;
}

const char *text_hashmap_iterator_next(text_hashmap_iterator_t *iterator, uint64_t *key)
{
    *key = iterator->map->nodes[iterator->index].key;
    return iterator->map->nodes[iterator->index++].value;
}
