/*
 * prompt.h
 */

#ifndef __PROMPT_H__
#define __PROMPT_H__

//Shows a prompt on screen
//Prints a question from |q|, followed by list of options
//in format:
//ans[i] - descs[i]
//
//all in a prompt with given height and width
//WARNIG - some answers may be invisible due to limited size
//the prompt will be centered on the screen
char p_ask(const char *q, unsigned short height, unsigned int width,
        const char *ans, const char** descs);

#endif /* __PROMPT_H__ */
