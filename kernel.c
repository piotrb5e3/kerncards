/*
 *  kernel.c
 *  parts of code by Arjun Sreedharan
 *  www.arjunsredharan.org
 */
#include "kwrite.h"

void kmain(void)
{
    const char *str = "my first kernel";
    setcol(GREEN);
    setbg(LIGHT_BLUE);
    clear();
    gotoxy(0,0);
    writestr(str);
    gotoxy(1,3);
    writestr("Testing\nAgain  Now\n\nWATT?");
    writexy("A long time ago\nin a galaxy far, far away\n\nDUDUDUDUDUD", 30, 1);
    writestr("Kappa\nKeepo");
    return;
}
