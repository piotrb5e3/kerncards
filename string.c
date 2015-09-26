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

unsigned int strlen(const char *str)
{
    unsigned int length = 0;
    while(str[length] != '\0')
        length++;
    return length;
}

unsigned int csubs(char *str, char regex, char sub)
{
    unsigned int num = 0;
    unsigned int i = 0;
    while(str[i]!='\0'){
        if(str[i] == regex){
            str[i] = sub;
            num++;
        }
        i++;
    }
    return num;
}

void strcpy(const char *from, char *to, unsigned int length)
{
    unsigned int i = 0;
    while(from[i]!='\0' && i<length){
        to[i]=from[i];
        i++;
    }
    to[i] = '\0';
}
