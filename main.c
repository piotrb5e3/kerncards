/*
 * main.c
 */

#include "keyboard.h"
#include "kwrite.h"
#include "string.h"
#include "time.h"
#include "random.h"
#include "kernel.h"
#include "idt.h"
#include "card.h"
#include "prompt.h"
#include "deck.h"

//Simple callback function for keyboard events:
int simple_callback(char c)
{
    char mstr[2];
    mstr[0] = c;
    mstr[1] = '\0';
    writexy("LAST PRESSED KEY:", 0 ,20);
    writexy(mstr, 20, 20);
    return 0;
}

//============= Main function
void kmain(void)
{
        char sttr[40];
        char str1[100] = "ANANANANANNANANANANNANNA";
        char str2[100] = "am\nam\nam\nam am am\n am";
        unsigned long num =0;
        unsigned long i =0;
        struct t_card card1, card2, card3, card4, card5;
        struct t_deck deck1, deck2, deck3;
	clear();
	idt_init();
        kbd_set_callback(simple_callback);
	kbd_enable();
        itostr(time_grab(), 40, sttr);
        writexy("TIMESTAMP: ", 0,4);
        writexy(sttr, 15, 4);
        
        //Let's write some random numbers:
        srand(time_grab());
        writexy("Some random numbers:", 30, 0);
        for(i = 0; i<10 ; i++){
            itostr(random(2048), 40, sttr);
            writexy(sttr, 30, i+1);
        }

        //Calculate avg from 1000 random nums
        num =0;
        for( i =0; i<1000000; i++)
            num += random(2048);
        num/=1000000;
        writexy("Average:(from 1M rolls)", 30, 12);
        itostr(num, 40, sttr);
        writexy(sttr, 30, 13);

        //Wait for keypress:
        asm("hlt;");

        //Lets print some cards!

        c_init(&card1, SPADE, QUEEN);
        c_init(&card2, HEART, ACE);
        c_init(&card3, CLUB, KING);
        c_init(&card4, DIAMOND, SIX);
        c_init(&card5, DIAMOND, TEN);
        c_drawxy(card1, 15, 14);
        c_drawxy(card2, 25, 14);
        c_drawxy(card3, 35, 14);
        c_drawxy(card4, 45, 14);
        c_drawxy(card5, 55, 14);

        //Lets fold some strings
        strfold(str1, 100, 5);
        writexy(str1, 50, 2);
        strfold(str2, 100, 3);
        writexy(str2, 50, 10);

        //Lets do some decking
        d_setup(&deck1);
        d_shuffle(&deck1);
        d_init(&deck2);
        d_init(&deck3);
        d_print(&deck1, 10, 10);
        d_put_top(&deck2, d_draw(&deck1));
        d_hide(&deck1);
        d_print(&deck1, 20, 10);
        d_put_top(&deck2, card1);
        d_put_top(&deck2, card2);
        d_put_top(&deck2, card3);
        d_put_top(&deck2, card4);
        d_put_top(&deck2, card5);
        for(int i = 0; i<15 ;i++)
            d_put_top(&deck3, d_draw(&deck1));
        d_show(&deck3);
        d_print_v(&deck2, 0, 0);
        d_print_h(&deck3, 10, 0);

        //Lets print a prompt
        p_ask(0, 20, 5, 0, 0);


	while(1){
         //   itostr(time_grab(), 40, sttr);
         //   writexy("TIMESTAMP: ", 0,4);
         //   writexy(sttr, 15, 4);
        }

}
