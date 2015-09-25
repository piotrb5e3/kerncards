#include "kwrite.h"

//Consts:
const char NEWLINE_C = '\n';
const short MAX_X = 80;
const short MAX_Y = 25;
//Variables:
short xpos=0, ypos=0;
enum t_color fg=LIGHT_GREY, bg=BLACK;
short attr = (BLACK*0x10)+LIGHT_GREY;
char *vidptr = (char*)0xb8000;  //video mem begins here.


//Calculate position for videomemory
unsigned int cal_pos(void)
{
    return 2*( ypos*MAX_X + xpos );
}

//Advance cursor by one 
void adv_pos(void)
{
    if(xpos<MAX_X-1)
        xpos++;
    else
        if(ypos<MAX_Y-1){
            xpos = 0;
            ypos++;
        }else{
            xpos=0;
            ypos=0;
        }
}

//Advance to next line
void adv_ln(void)
{
    if(ypos<MAX_Y-1){
        xpos = 0;
        ypos++;
    }else{
        xpos = 0;
        ypos = 0;
    }
}

//__Implementation of kwrite.h__
short gotoxy(short x, short y)
{
    if(x<0||x>=MAX_X||y<0||y>=MAX_Y)
        return -1;
    xpos = x;
    ypos = y;
    return 0;
}


short writestr(const char *str)
{
    unsigned int j = 0;
    unsigned int tmp = -1;
    while (str[j] != '\0'){
        //Check if we should go to a new line
        if(str[j] == NEWLINE_C){
            adv_ln();
            j++;
        }
        else{
            tmp = cal_pos();
            vidptr[tmp] = str[j];
            vidptr[tmp+1] = attr;
            adv_pos();
            j++;
        }
    }
    return 0;
}

short writexy(const char *str, short x, short y)
{
    unsigned int j = 0;
    unsigned int tmp = -1;
    int t_x, t_y;
    if(x<0||x>=MAX_X||y<0||y>=MAX_Y)
        return -1;
    t_x = x;
    t_y = y;
    while (str[j] != '\0'){
        //Check if we should go to a new line
        if(str[j] == NEWLINE_C){
            t_x = x;
            t_y++;
            j++;
        }
        else{
            tmp = 2 * (t_y * MAX_X + t_x);
            vidptr[tmp] = str[j];
            vidptr[tmp+1] = attr;
            if(t_x < MAX_X - 1)
                t_x++;
            else
                if(t_y < MAX_Y - 1){
                    t_x = x;
                    t_y++;
                }else{
                    t_x = x;
                    t_y = y;
                }
            j++;
        }
    }
    return 0;
}

short setcol(enum t_color col)
{
    if(col<BLACK ||col>WHITE)
        return -1;
    fg = col;
    //Update attr:
    attr = (bg*0x10)+fg;
    return 0;
}

short setbg(enum t_color col)
{
    if(col<BLACK ||col>WHITE)
        return -1;
    bg = col;
    //Update attr:
    attr = (bg*0x10)+fg;
    return 0;
}

void clear(void)
{
    unsigned int i = 0;
    while(i<MAX_X*MAX_Y*2){
        vidptr[i] = ' ';
        vidptr[i+1] = attr;
        i+=2;
    }
}
