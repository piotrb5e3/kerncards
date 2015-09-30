/*
 * card.h
 */

#ifndef __CARD_H__
#define __CARD_H__

//Enum for representing wether card is showing front, or back
enum t_side {BACK=0, FRONT=1};

//Enum for representing suit of a card
enum t_suit {SPADE=0, DIAMOND, CLUB, HEART, S_END};

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
    KING,
    R_END
};

//Struct representing a card
struct t_card{
    enum t_suit suit;
    enum t_rank rank;
    enum t_side side; //0 if card is face-down
};

//========Card functions

//Initialise a card
//Cards are always initialised face-up
void c_init(struct t_card *card, enum t_suit s, enum t_rank r);

//Draw a card with top-left corner at given xy position
//It draws face-down cards correctly
void c_drawxy(struct t_card card, unsigned short x, unsigned short y);

//Flip a card
void c_flip(struct t_card *card);

//Hide card
void c_hide(struct t_card *card);

//Show card
void c_show(struct t_card *card);


#endif /* __CARD_H__ */
