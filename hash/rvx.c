#include <stdio.h>
#include <string.h>
#include "hash.h"

#define N 10

typedef struct Book
{
    char title[10];
    int pages;
} Book;

int cmp_data(void *, void *);
int hfunc(void *, int);
void init_books(Book *, int);

int main()
{
    Hash *hash = hash_init(30, hfunc, cmp_data);
    Book libr[N];
    init_books(libr, N);

    hash_add(hash, &libr[0], "Monday");
    hash_add(hash, &libr[1], "Tuesday");
    hash_add(hash, &libr[2], "Sunday");
    hash_add(hash, &libr[3], "Friday");
    hash_add(hash, &libr[4], "September");
    hash_add(hash, &libr[5], "October");
    hash_add(hash, &libr[6], "Moscwo");
    hash_add(hash, &libr[7], "New");
    hash_add(hash, &libr[7], "New");
    hash_add(hash, &libr[7], "New");
    hash_add(hash, &libr[7], "New");
    hash_add(hash, &libr[7], "New");
    hash_print(hash);
    HNode *result = hash_search(hash, &libr[4], "September");
    printf(" %s %d %s \n", ((Book *)result->key)->title, ((Book *)result->key)->pages, (char *)result->data);

    hash_destr(&hash);
    return 0;
}

void init_books(Book *books, int size)
{
    strcpy(books[0].title, "Book 1");
    strcpy(books[1].title, "Book 8");
    strcpy(books[2].title, "Book 2");
    strcpy(books[3].title, "Book 3");
    strcpy(books[4].title, "Book 4");
    strcpy(books[5].title, "Book 5");
    strcpy(books[6].title, "Book 6");
    strcpy(books[7].title, "Book 7");
    books[0].pages = 100;
    books[1].pages = 110;
    books[2].pages = 120;
    books[3].pages = 130;
    books[4].pages = 140;
    books[5].pages = 150;
    books[6].pages = 170;
    books[7].pages = 300;
}

int hfunc(void *key, int mod)
{
    Book *c_key = key;
    size_t len = strlen(c_key->title);
    int result = 0, pmul = 7, p = 1;
    for (size_t i = 0; i < len; i++)
    {
        result += c_key->title[i] * p;
        p *= pmul;
    }
    result += 100000 * c_key->pages;

    return result % mod;
}

int cmp_data(void *data_1, void *data_2)
{
    int res = strcmp(((Book *)data_1)->title, ((Book *)data_2)->title);
    if (!res)
    {
        if (((Book *)data_1)->pages > ((Book *)data_2)->pages)
            res = 1;
        else if (((Book *)data_1)->pages < ((Book *)data_2)->pages)
            res = -1;
        else
            res = 0;
    }
    return res;
}
