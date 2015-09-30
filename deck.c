/*
 * deck.c
 */

#include "deck.h"
#include "random.h"
//========== Public functions
void d_init(struct t_deck *deck)
{
    deck->numcards = 0;
}

void d_setup(struct t_deck *deck)
{
    enum t_suit s = SPADE;
    enum t_rank r = ACE;
    struct t_card card;
    
    //"Empty" the deck
    deck->numcards = 0;

    while(s < S_END){
        while(r < R_END){
            c_init(&card, s, r);
            d_put_top(deck, card);
            r++;
        }
        r = ACE;
        s++;
    }
}

void d_hide(struct t_deck *deck)
{
    unsigned int i;
    for(i = 0; i<deck->numcards; i++){
        c_hide(&(deck->cards[i]));
    }
}

void d_show(struct t_deck *deck)
{
    unsigned int i;
    for(i = 0; i<deck->numcards; i++){
        c_show(&(deck->cards[i]));
    }

}
struct t_card d_draw(struct t_deck *deck)
{
    struct t_card result;
    result = deck->cards[deck->numcards - 1];
    deck->numcards--;
    return result;
}

//Randomly shuffles given deck
void d_shuffle(struct t_deck *deck)
{
    //Fisher-Yates shuffle
    //Also "Algorithm P." from "The Art of Computer Programming"
    unsigned int i = 0, j = 0;
    struct t_card tmp;

    for(i = deck->numcards - 1; i >= 1 ; i--){
        j = random(i);
        //Swap ith and jth card
        if(i != j){
            tmp = deck->cards[i];
            deck->cards[i] = deck->cards[j];
            deck->cards[j] = tmp;
        }
    }
}

void d_put_top(struct t_deck *deck, const struct t_card card)
{
    if(deck->numcards + 1 >= MAX_CARDS){
        //TODO: panic!
    }
    deck->cards[deck->numcards] = card;
    deck->numcards++;
}

void d_put_bot(struct t_deck *deck, const struct t_card card)
{
    unsigned int i = 0;
    if(deck->numcards + 1 >= MAX_CARDS){
        //TODO: panic!
    }
    //Move all cards one position up
    for(i = deck->numcards; i>0 ;i--){
        deck->cards[i] = deck->cards[i - 1];
    }

    //insert the card at the bottom
    deck->cards[0] = card;
    deck->numcards++;
}


void d_add_all(struct t_deck *deck, struct t_deck *from)
{
    if(deck->numcards + from->numcards > MAX_CARDS){
        //TODO panic
    }

    while(!d_empty(from)){
        d_put_top(deck, d_draw(from));
    }
}

void d_flip_top(struct t_deck *deck)
{
    c_flip(&(deck->cards[deck->numcards - 1]));
}

void d_print(struct t_deck *deck, unsigned short x, unsigned short y)
{
    c_drawxy(deck->cards[deck->numcards - 1], x, y);
}

//Draw the deck with topmost card on the bottom of the screen
// ____
//|3  S|
// ____
//|A  C|
//......
//......
void d_print_v(struct t_deck *deck, unsigned short x, unsigned short y)
{
    unsigned int i = 0;

    for(i = 0; i<deck->numcards ;i++){
        c_drawxy(deck->cards[i], x, y + (2 * i));
    }
}

//Draw the deck with topmost card to the right
//|3|A...
//| | ...
//|S|C...
void d_print_h(struct t_deck *deck, unsigned short x, unsigned short y)
{
    unsigned int i = 0;

    for(i = 0; i<deck->numcards ;i++){
        c_drawxy(deck->cards[i], x + (2 * i), y);
    }

}

short d_empty(const struct t_deck *deck)
{
    return deck->numcards == 0;
}

