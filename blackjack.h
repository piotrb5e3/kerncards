/*
 * blackjack.h
 * interface for blackjack module
 */

#ifndef __BLACKJACK_H__
#define __BLACKJACK_H__

//Set up the game
void blackjack_init(void);

//Callback function for the game of blackjack
int blackjack_callback(char c);

#endif /* __BLACKJACK_H__ */
