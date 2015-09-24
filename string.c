/*
 * string.c
 */

#include "string.h"

int itostr(unsigned long number, unsigned int strlen, char *str)
{
    unsigned int ptr = 0;
    unsigned int len = 0;
    char tmp = 'x';
    //Dismantle
    while(number>9 && ptr<strlen-1){
        str[ptr]=number%10 + '0';
        number/=10;
        ptr++;
    }
    if(ptr>=strlen-1)
        return -1;
    str[ptr] = number + '0';
    ptr++;
    //Reverse
    len = ptr;
    for(ptr=0; 2*ptr<len-1 ;ptr++){
        tmp = str[ptr];
        str[ptr] = str[len - 1 - ptr];
        str[len - 1 - ptr] = tmp;
    }
    str[len] = '\0';
    return 0;
}
