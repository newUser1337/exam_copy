#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define PRIME 8

HNode *_hash_create_node(void *, void *);
void _hash_destr_node(HNode **);
int _hash_get_new_bufsize(int);
void _hash_rehash(Hash *, int);
void _hash_resize(Hash *);
int _hash_get_new_modsize(int);
unsigned long primes[PRIME] = {41, 103, 509, 997, 2767, 3727, 5737, 8863};

Hash *hash_init(int modsize, int (*hfunc)(void *, int), int (*cmp)(void *, void *))
{
    Hash *hash = (Hash *)malloc(sizeof(Hash));
    hash->modsize = modsize;
    hash->size = 0;
    hash->hfunc = hfunc;
    hash->cmp = cmp;
    hash->array = (HNode **)malloc(sizeof(HNode *) * modsize);
    // printf("create array\n");
    // printf("create hash\n");
    for (int i = 0; i < modsize; i++)
        hash->array[i] = NULL;

    return hash;
}

void hash_destr(Hash **hash)
{
    for (int i = 0; i < (*hash)->modsize; i++)
        if ((*hash)->array[i] != NULL)
            _hash_destr_node(&(*hash)->array[i]);
    free((*hash)->array);
    free(*hash);
    *hash = NULL;
    // printf("destr hash\n");
    // printf("destr array\n");
}
void _hash_destr_node(HNode **node)
{
    free(*node);
    *node = NULL;
    // printf("destr node\n");
}
HNode *hash_add(Hash *hash, void *key, void *data)
{
    HNode *node = _hash_create_node(key, data);
    hash->size++;
    _hash_resize(hash);
    int index = hash->hfunc(key, hash->modsize);
    while (hash->array[index % hash->modsize] != NULL)
        index++;
    hash->array[index % hash->modsize] = node;

    return node;
}

HNode *_hash_create_node(void *key, void *data)
{
    HNode *node = (HNode *)malloc(sizeof(HNode));
    node->key = key;
    node->data = data;
    // printf("create node\n");
    return node;
}

HNode *hash_search(Hash *hash, void *key, void *data)
{
    int index = hash->hfunc(key, hash->modsize);
    while (hash->array[index % hash->modsize] != NULL && hash->cmp(hash->array[index % hash->modsize]->data, data))
        index++;

    return hash->array[index % hash->modsize];
}

void _hash_resize(Hash *hash)
{
    float bound = (float)hash->size * 100 / hash->modsize;
    if (bound < 25.0)
        return;
    int mod_size_temp = hash->modsize;
    hash->modsize = _hash_get_new_modsize(2 * hash->modsize);
    _hash_rehash(hash, mod_size_temp);
}

int _hash_get_new_modsize(int n)
{
    for (int i = 0; i < PRIME; i++)
        if (n < primes[i])
            return primes[i];
    return n;
}

void _hash_rehash(Hash *hash, int prev_modsize)
{
    HNode **r_array = (HNode **)malloc(sizeof(HNode *) * hash->modsize);
    // printf("create array\n");
    for (int i = 0; i < prev_modsize; i++)
    {
        if (hash->array[i] != NULL)
        {
            int new_index = hash->hfunc(hash->array[i]->key, hash->modsize) % hash->modsize;
            while (r_array[new_index % hash->modsize] != NULL)
                new_index++;
            r_array[new_index] = hash->array[i];
        }
    }
    free(hash->array);
    // printf("destr array\n");
    hash->array = r_array;
}

void hash_print(Hash *hash)
{
    for (int i = 0; i < hash->modsize; i++)
        if (hash->array[i] != NULL)
            printf("index %d, key %s \n", i, (char*)hash->array[i]->key);
}