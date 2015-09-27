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
        unsigned long num =0;
        unsigned long i =0;
        struct t_card card1, card2, card3, card4, card5;
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
        p_ask(0, 20, 5, 0, 0);

	while(1){
         //   itostr(time_grab(), 40, sttr);
         //   writexy("TIMESTAMP: ", 0,4);
         //   writexy(sttr, 15, 4);
        }

}
