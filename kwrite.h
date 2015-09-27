/*
 * kwrite.h
 *
 * Header for screenwriter
 */

#ifndef __KWRITE_H__
#define __KWRITE_H__

//========== Constants
extern const short MAX_X;
extern const short MAX_Y;

//========== Types

//Color enum:
enum t_color{
    BLACK=0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE,
};

//Public functions

/*
 * Move writing cursor to position (x, y)
 *
 * returns 0 at success, <0 at failure
 */
short gotoxy(short x, short y);

/*
 * Write string at current cursor position
 *
 * returns 0 at success, <0 at failure
 */
short writestr(const char *str);

/*
 * Write string at given position - newlines go to (start_x, next_y)
 *
 * DOES NOT CHANGE POINTER!
 *
 * returns 0 at success, <0 at failure
 */
short writexy(const char *str, short x, short y);

/*
 * Set writng color 
 *
 * returns 0 at success, <0 at failure
 */
short setcol(enum t_color col);

/*
 * Set writing background color
 *
 * returns 0 at success, <0 at failure
 */
short setbg(enum t_color col);

/*
 * Clear screen using current colors
 */
void clear(void);

#endif /*__KWRITE_H__*/
