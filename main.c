#include <msp430.h>
#include "game.h"
#include "LCD.h"
#include "button.h"

void init_timer();
void init_buttons();

int main(void)
{
		WDTCTL = WDTPW|WDTHOLD;
		char * Msg1 = "GAME OVER";
		char * Msg2 = "GAME WON";
	    initSPI();
	    LCDinit();
	    LCDclear();

	    init_timer();
	    init_buttons();
	    __enable_interrupt();

        unsigned char player = initPlayer();

        while(1)
        {



        }

        return 0;
}

//
// YOUR TIMER A ISR GOES HERE
//

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
    P1REN |= BIT1|BIT2||BIT4;                   // enable internal pull-up/pull-down network
    P1OUT |= BIT1|BIT2|BIT3|BIT4;                   // configure as pull-up
    P1IFG &= ~(BIT1|BIT2|BIT3);                // clear flags

}
        // do button initialization work

