#include <msp430.h>
#include "game.h"
#include "LCD.h"
#include "button.h"

void init_timer();
void init_buttons();

char HIT = 0;
char MOVE = 0;
char BUTTON = 0;
char FLAG = 0;
char PLAY = 1;
//char WIN = 0;
unsigned char player;
char * Msg1 = "Game";
char * Msg2 = "Over";
char * Msg3 = "YOU";
char * Msg4 = "WON";


int main(void)
{
		WDTCTL = WDTPW|WDTHOLD;

	    initSPI();
	    LCDinit();
	    LCDclear();

	    init_timer();
	    init_buttons();
	    __enable_interrupt();

        player = initPlayer();
        printPlayer(player);
        while(PLAY)
        {
        	player = initPlayer();
        	printPlayer(player);
        	if(HIT){
        		HIT = 0;
        		player = movePlayer(player, BUTTON);
        	}
        	if(PLAY == 1){
        		cursorToLineOne();
        		writeString(Msg1);
        		cursorToLineTwo();
        		writeString(Msg2);
        	}
//        	if(WIN =1){
//        		cursorToLineOne();
//        		writeString(Msg3);
//        		cursorToLineTwo();
//        		writeString(Msg4);
//        	}
//
//        }

        return 0;
}

//
// YOUR TIMER A ISR GOES HERE
//
void testAndRespondToButtonPush(char buttonToTest){
    if (buttonToTest & P1IFG){
       if (buttonToTest & P1IES)
	   {
		movePlayer(player, buttonToTest);
		FLAG = 0;
		PLAY = 1;
		MOVE = 1;
		BUTTON = buttonToTest;
		} else
		{
			debounce();
		}

		P1IES ^= buttonToTest;
		P1IFG &= ~buttonToTest;
            }
        }


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	//BIT1-4 are defined in MSP library
  testAndRespondToButtonPush(BIT1);
  testAndRespondToButtonPush(BIT2);
  testAndRespondToButtonPush(BIT3);
  testAndRespondToButtonPush(BIT4);

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    TACTL &= ~TAIFG;            // clear interrupt flag
    FLAG++;
    if(FLAG >= 4){
       PLAY = 0;
    }
}

void init_timer()
{
	    TACTL &= ~(MC1|MC0);        // stop timer
	    TACTL |= TACLR;             // clear TAR
	    TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?
	    TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?
	    TACTL &= ~TAIFG;            // clear interrupt flag
	    TACTL |= MC1;               // set count mode to continuous
	    TACTL |= TAIE;              // enable interrupt
}

void init_buttons()
{	configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);

    P1DIR &= ~(BIT1|BIT2|BIT3|BIT4);                // set buttons to input
    P1IE |= BIT1|BIT2|BIT3|BIT4;                 // enable the interrupts
    P1IES |= BIT1|BIT2|BIT3|BIT4;                   // configure interrupt to sense falling edges
    P1REN |= BIT1|BIT2|BIT3|BIT4;                   // enable internal pull-up/pull-down network
    P1OUT |= BIT1|BIT2|BIT3|BIT4;                   // configure as pull-up
    P1IFG &= ~(BIT1|BIT2|BIT3);                // clear flags

}
        // do button initialization work

