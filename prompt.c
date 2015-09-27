/*
 * prompt.c
 */

#include "prompt.h"
#include "string.h"
#include "kwrite.h"

#define FRAME_CHAR '#'
//========== Constants
//========== Variables
unsigned long last_char_rev;
//========== Private functions
void print_frame(unsigned short width, unsigned short height)
{
    char tmp[100];//= "####################utetrabhbervacwygr";
    unsigned int i = 0;
    unsigned short startx = (MAX_X - width)/2;
    unsigned short starty = (MAX_Y - height)/2;
    i = 0;
    while(i<width){
        tmp[i]=FRAME_CHAR;
        i++;
    }


    tmp[width] = 0;
    writexy(tmp, startx, starty);
    writexy(tmp, startx, starty + height - 1);

    for(i = 1; i<width - 1; i++)
        tmp[i] = ' ';
    for(i = 1; i<height - 1; i++)
        writexy(tmp, startx, starty + i);
}
//========== Public functions
char p_ask(const char *q, unsigned short width, unsigned int height,
        const char *ans, const char** descs)
{
    print_frame(width, height);
    return 0;
}


