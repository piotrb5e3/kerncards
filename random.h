/*
 * random.h
 */

#ifndef __RANDOM_H__
#define __RANDOM_H_

//Get random long int from given range [lo, hi]
long int rand(long int lo, long int hi);

//Get random long from range [0, hi]
unsigned long int random(unsigned long int hi);

//Set seed
void srand(unsigned long int seed);


#endif /* __RANDOM_H__ */
