#ifndef __SPARCE__
#define __SPARCE__

typedef struct Sparce
{
    int **ST;
    int log;
    int *X; 
} Sparce;

Sparce *sparce_init(int *, int);
void sparce_print(Sparce *);
int sparce_rmq(Sparce *, int, int);
void sparce_destr(Sparce **);
#endif