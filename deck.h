/*
 * deck.h
 */

#ifndef __DECK_H__
#define __DECK_H__

#include "card.h"
//8 full decks are necesary for blackjack
#define MAX_CARDS (52)

//Struct for representing decks of cards
struct t_deck{ //Decks cannot exceed MAX_CARDS
    int numcards; //Nuber of cards - entries beyond this point shall be ignored
    //cards[numcards - 1] is the top of the deck
    //cards[0] is the bottom of the deck
    struct t_card cards[MAX_CARDS];
};


//Sets a deck as an empty deck
void d_init(struct t_deck *deck);

//Sets a deck as a basic, ordered by suit, by rank 52 card deck
//Deck is by default all face-up
void d_setup(struct t_deck *deck);

//Set all cards in the deck as face-down
void d_hide(struct t_deck *deck);

//Set all cards in the deck as face-up
void d_show(struct t_deck *deck);

//Draw a card from the top of the deck
struct t_card d_draw(struct t_deck *deck);

//Randomly shuffles given deck
void d_shuffle(struct t_deck *deck);

//Put a card on the top of a deck
void d_put_top(struct t_deck *deck, const struct t_card card);

//Put a cardmon the bottom of a deck
void d_put_bot(struct t_deck *deck, const struct t_card card);

//Put a whole deck on top of another deck, reversed, giving it all
//the cards
void d_add_all(struct t_deck *deck, struct t_deck *from);

//Flip top card
void d_flip_top(struct t_deck *deck);

//Draw the deck only showing the topmost card, face-up or face-down depending
//on its orientation
void d_print(struct t_deck *deck, unsigned short x, unsigned short y);

//Draw the deck with topmost card on the bottom of the screen
// ____
//|3  S|
// ____
//|A  C|
//......
//......
void d_print_v(struct t_deck *deck, unsigned short x, unsigned short y);

//Draw the deck with topmost card to the right
//|3|A...
//| | ...
//|S|C...
void d_print_h(struct t_deck *deck, unsigned short x, unsigned short y);

//Check if deck is empty
//0 -> not empty
//!0 -> empty
short d_empty(const struct t_deck *deck);

#endif /* __DECK_H__ */
