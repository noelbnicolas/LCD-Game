#include <msp430.h>
#include "game.h"
#include "button.c"
#include "button.h"
#include "LCD.c"
#include "LCD.h"

void init_timer();
void init_buttons();

int main(void)
{
		WDTCTL = WDTPW|WDTHOLD;





	    initSPI();
	    LCDinit();
	    LCDclear();

        unsigned char player = initPlayer();

        init_timer();
        init_buttons();
        __enable_interrupt();


        while(1)
        {

        	 char buttons[] = {BIT1, BIT2, BIT3, BIT4};
        	        char pressedButton = pollP1Buttons(buttons, 4);

        	        switch (pressedButton) {
        	            case BIT1:
        	                // do something in response
        	                break;
        	            case BIT2:
        	                // do something in response
        	            	 break;
        	            case BIT2:
        	                // do something in response
        	                break;
        	            case BIT4:
        	                // toggle LEDs and wait for release
        	                P1OUT ^= BIT0|BIT6;
        	                waitForP1ButtonRelease(BIT3);
        	                break;
                /*
                 * while (game is on)
                 * {
                 *                 check if button is pushed (you don't want to block here, so don't poll!)
                 *                 if button is pushed:
                 *                         clear current player marker
                 *                         update player position based on direction
                 *                         print new player
                 *                         clear two second timer
                 *                         wait for button release (you can poll here)
                 * }
                 *
                 * print game over or you won, depending on game result
                 *
                 * wait for button press to begin new game (you can poll here)
                 * wait for release before starting again
                 */
        }//nada

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
}
