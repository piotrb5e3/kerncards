/*
 * random.c
 */
#include "random.h"

unsigned long seed = 42; //100% random

static unsigned long step()
{
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed <<5;
    return seed;
}

long int rand(long int lo, long int hi)
{
    if(hi>=lo)
        return lo + step()%(hi - lo + 1);
    else
        return 0;
}

unsigned long int random(unsigned long int hi)
{
    return rand(0, hi);
}

void srand(unsigned long int s)
{
    unsigned int i, num;
    seed = s;
    num = random(10);
    for(i =0; i<num ; i++)
        step();
}
