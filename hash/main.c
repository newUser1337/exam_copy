#include <stdio.h>
#include <string.h>
#include "hash.h"

int cmp_data(void *, void *);
int hfunc(void *, int);

int main()
{
    char prog[5] = "prog";
    char prog_data[10] = "line";
    char key_1[5] = "zqwe";
    char key_2[5] = "zqwe";
    char key_3[5] = "car";
    char key_4[10] = "computer";
    char key_5[5] = "124";
    char key_6[15] = "yesterday";
    char key_7[15] = "monday";
    char key_8[15] = "Dallas";
    char key_9[15] = "Lakers";
    char key_10[15] = "Oklahoma";

    char data_1[100] = "My data";
    char data_2[100] = "Your data";
    char data_3[100] = "His data";

    Hash *hash = hash_init(30, hfunc, cmp_data);
    hash_add(hash, prog, prog_data);
    hash_add(hash, prog_data, prog);
    hash_add(hash, key_1, data_1);
    hash_add(hash, key_2, data_2);
    hash_add(hash, key_3, prog);
    hash_print(hash);
    printf("\n");
    hash_add(hash, key_4, prog);
    hash_add(hash, key_5, prog);
    hash_add(hash, key_5, prog);
    hash_add(hash, key_5, prog);
    hash_add(hash, key_5, prog);
    hash_add(hash, key_6, data_3);
    hash_add(hash, key_7, prog);
    hash_add(hash, key_8, prog);
    hash_add(hash, key_9, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_add(hash, key_10, prog);
    hash_print(hash);

    HNode *result = hash_search(hash, key_1, data_2);
    printf("%s %s", (char *)result->key, (char *)result->data);

    hash_destr(&hash);
    return 0;
}

int hfunc(void *key, int mod)
{
    char *c_key = key;
    size_t len = strlen(c_key);
    int result = 0, pmul = 7, p = 1;
    for (size_t i = 0; i < len; i++)
    {
        result += c_key[i] * p;
        p *= pmul;
    }

    return result % mod;
}

int cmp_data(void *data_1, void *data_2)
{
    return strcmp((char *)data_1, (char *)data_2);
}
