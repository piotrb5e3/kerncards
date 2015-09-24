/*
 * card.h
 */

#ifndef __CARD_H__
#define __CARD_H__
//Max number of cards in a deck, defined in card.c
extern const int MAX_CARDS;

//Enum for representing wether card is showing front, or back
enum t_side {BACK=0, FRONT=1}

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
};

//Struct for representing decks of cards
//Card at 
struct t_deck{ //Decks cannot exceed MAX_CARDS
    int numcards=0;
    struct t_card cards[MAX_CARS];

};

//========Card functions

//Sets a deck as a basic, ordered by suit, by rank 52 card deck
void deck_setup(struct t_deck &deck);

//Randomly shuffles given deck
void deck_shuffle(struct t_deck &deck);

#endif /* __CARD_H__ */
