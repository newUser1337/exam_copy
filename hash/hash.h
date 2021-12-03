#ifndef __HASH__
#define __HASH__

typedef struct HNode
{
    void *key;
    void *data;
} HNode;

typedef struct Hash
{
    HNode **array;
    int modsize;
    int size;
    int (*hfunc)(void *, int);
    int (*cmp)(void *, void *);
} Hash;

Hash *hash_init(int, int (*)(void *, int), int (*)(void *, void *));
void hash_destr(Hash **);
HNode *hash_add(Hash *, void *, void *);
HNode *hash_search(Hash *, void *, void *);
void hash_print(Hash *);

#endif