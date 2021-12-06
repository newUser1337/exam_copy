#include <stdio.h>
#include <stdlib.h>
#include "sparce.h"

void _fill_ST(Sparce *, int *);
int _set_elemet(int **, int *, int, int);
int _min(int, int);
int _get_log(int);

Sparce *sparce_init(int *array, int size)
{
    Sparce *sp = (Sparce *)malloc(sizeof(Sparce));
    sp->log = _get_log(size);
    sp->ST = (int **)malloc(sizeof(int *) * sp->log);
    sp->X = (int *)malloc(sizeof(int) * sp->log);
    sp->X[0] = size;
    int m = size;
    for (int i = 0; i < sp->log; i++)
    {
        if (i)
            m -= (1 << (i - 1));
        sp->X[i] = m;
        sp->ST[i] = (int *)malloc(sizeof(int) * sp->X[i]);
    }
    _fill_ST(sp, array);

    return sp;
}

void _fill_ST(Sparce *sp, int *array)
{
    for (int i = 0; i < sp->X[0]; i++)
        sp->ST[0][i] = array[i];

    for (int j = 1; j < sp->log; j++)
        for (int i = 0; i < sp->X[j]; i++)
            sp->ST[j][i] = _set_elemet(sp->ST, array, j - 1, i);
}

int _set_elemet(int **ST, int *array, int log, int index)
{
    return _min(ST[log][index], ST[log][index + (1 << log)]);
}

int _min(int a, int b)
{
    return a < b ? a : b;
}

int _get_log(int in)
{
    int i;
    for (i = 0; in; in >>= 1, i++)
        ;

    return i;
}

void sparce_print(Sparce *sp)
{
    for (int j = 0; j < sp->log; j++)
    {
        for (int i = 0; i < sp->X[j]; i++)
            printf("%3d ", sp->ST[j][i]);
        printf("\n");
    }
}

int sparce_rmq(Sparce *sp, int r, int l)
{
    if (!(r > l && sp->X[0] > r && l > -1))
        return 0;

    int log = _get_log(r - l) - 1;
    if (log)
        return _min(sp->ST[log][l], sp->ST[log][r - (1 << log) + 1]);
    else
        return sp->ST[log][l];
}

void sparce_destr(Sparce **spar)
{
    for (int i = 0; i < (*spar)->log; i++)
    {
        free((*spar)->ST[i]);
    }
    free((*spar)->X);
    free((*spar)->ST);
    free(*spar);
    *spar = NULL;
}