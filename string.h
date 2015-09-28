/*
 * string.h
 */

#ifndef __STRING_H__
#define __STRING_H__

//Convert a number to its string, decimal representation
//return 0 on success, -1 otherwise
int itostr(unsigned long number, unsigned int strlen, char *str);


//Get length of a null ('\0') terminated string
unsigned int strlen(const char *str);

//Substitute all occurences of character |regex| for |sub| in
//given, null terminated, string str 
unsigned int csubs(char *str, char regex, char sub);

//Copy at most |length| chars from |from| to |target|
void strcpy(const char *from, char *to, unsigned int length);

//Fold a given string(by inserting '\n's to fit certain width.
//Tries to fold on spaces. If necesary, can fold inside words
//maxlength is the maximum available length of *str
//returns number of line breaks included in text after folding
unsigned int strfold(char *str, const unsigned int maxlength, unsigned int width);

#endif /* __STRING_H__ */
