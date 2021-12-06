#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sparce.h"

#define SIZE 17

int main()
{
    int array[SIZE] = {2, 6, -3, 5, -7, 2, -8, 3, -5, -2, 11, -20, 4, -4, -6, -4, -21};
    Sparce *sp = sparce_init(array, SIZE);
    sparce_print(sp);

    int r = 16;
    int l = 1;
    int res = sparce_rmq(sp, r, l);

    printf("res  %d\n", res);

    sparce_destr(&sp);

    return 0;
}
