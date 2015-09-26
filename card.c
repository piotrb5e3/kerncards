/*
 * card.c
 */
#include "card.h"
#include "string.h"
#include "kwrite.h"

//====== Constants

#define SUIT_SIGN_REGEX '%'
#define SUIT_LETTER_REGEX '$'

//Array holding strings for card ranks, each is 2 characters
//Addresable with enum t_rank
//rank_s[0] is the card back
const char *rank_s[] = {
        " _____ \n"
        "|     |\n"
        "| XXX |\n"
        "| XXX |\n"
        "| XXX |\n"
        "|_____|",/* No card is '0', so I put the cardback here*/
        " _____ \n"
        "|A   $|\n"
        "|     |\n"
        "|  %  |\n"
        "|     |\n"
        "|$___A|",
        " _____ \n"
        "|2   $|\n"
        "|  %  |\n"
        "|     |\n"
        "|  %  |\n"
        "|$___2|",
        " _____ \n"
        "|3   $|\n"
        "| % % |\n"
        "|     |\n"
        "|  %  |\n"
        "|$___3|",
        " _____ \n"
        "|4   $|\n"
        "| % % |\n"
        "|     |\n"
        "| % % |\n"
        "|$___4|",
        " _____ \n"
        "|5   $|\n"
        "| % % |\n"
        "|  %  |\n"
        "| % % |\n"
        "|$___5|",
        " _____ \n"
        "|6   $|\n"
        "| % % |\n"
        "| % % |\n"
        "| % % |\n"
        "|$___6|",
        " _____ \n"
        "|7   $|\n"
        "| % % |\n"
        "|% % %|\n"
        "| % % |\n"
        "|$___7|",
        " _____ \n"
        "|8   $|\n"
        "|% % %|\n"
        "| % % |\n"
        "|% % %|\n"
        "|$___8|",
        " _____ \n"
        "|9   $|\n"
        "|% % %|\n"
        "|% % %|\n"
        "|% % %|\n"
        "|$___9|",
        " _____ \n"
        "|10  $|\n"
        "|% % %|\n"
        "|%% %%|\n"
        "|% % %|\n"
        "|$__10|",
        " _____ \n"
        "|J   $|\n"
        "|   ww|\n"
        "| % {)|\n"
        "| c=X |\n"
        "|$_XXJ|",
        " _____ \n"
        "|Q   $|\n"
        "|   ww|\n"
        "| % {(|\n"
        "| c=XX|\n"
        "|$_XXQ|",
        " _____ \n"
        "|K   $|\n"
        "|   WW|\n"
        "| % {)|\n"
        "| c=XX|\n"
        "|$_XXK|",
};

//Array holding characters for card suit signs
//Addresable with t_suit
const char suit_s[] = {
    '^',/* SPADE */
    'O',/* DIAMOND */
    '&',/* CLUB */
    'V',/* HEART */
};
//Array holding characters for card suit letters
//Addresable with t_suit
const char suit_c[] = {
    'S',/* SPADE */
    'D',/* DIAMOND */
    'C',/* CLUB */
    'H',/* HEART */
};
//====== Structs
//====== Variables

//====== Private functions


//====== Public functions

void c_init(struct t_card *card, enum t_suit s, enum t_rank r)
{
    card->suit = s;
    card->rank = r;
    card->side = FRONT;
}

void c_drawxy(struct t_card card, unsigned short x, unsigned short y)
{
    char c_img[50]="ERRRRRR\n";
    if(card.side == FRONT){
        strcpy(rank_s[card.rank], c_img, 49);
        csubs(c_img, SUIT_SIGN_REGEX, suit_s[card.suit]);
        csubs(c_img, SUIT_LETTER_REGEX, suit_c[card.suit]);
    }else{
        strcpy(rank_s[0], c_img, 49);
    }
    writexy(c_img, x, y);
}
