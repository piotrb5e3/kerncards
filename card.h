/*
 * card.h
 */

#ifndef __CARD_H__
#define __CARD_H__
//Max number of cards in a deck, defined in card.c
#define MAX_CARDS 52

//Enum for representing wether card is showing front, or back
enum t_side {BACK=0, FRONT=1};

//Enum for representing suit of a card
enum t_suit {SPADE=0, DIAMOND, CLUB, HEART};

//Enum for representing rank of a card
enum t_rank {
    ACE=1,
    DEUCE,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

//Struct representing a card
struct t_card{
    enum t_suit suit;
    enum t_rank rank;
    enum t_side side; //0 if card is face-down
};

//Struct for representing decks of cards
struct t_deck{ //Decks cannot exceed MAX_CARDS
    int numcards;
    struct t_card cards[MAX_CARDS];
};

//========Card functions

//Initialise a card
//Cards are always initialised face-up
void c_init(struct t_card *card, enum t_suit s, enum t_rank r);

//Draw a card with top-left corner at given xy position
//It draws face-down cards correctly
void c_drawxy(struct t_card card, unsigned short x, unsigned short y);

//Sets a deck as a basic, ordered by suit, by rank 52 card deck
//TODO move to deck module, implement
//void deck_setup(struct t_deck &deck);

//Randomly shuffles given deck
//TODO move to deck module, implement
//void deck_shuffle(struct t_deck &deck);

#endif /* __CARD_H__ */
