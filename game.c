#include <msp430g2553.h>
#include "game.h"
#include "LCD.c"

unsigned char initPlayer()
{
        return 0x80;
}

void printPlayer(unsigned char player)
{
        writeCommandByte(player);
        writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
        writeCommandByte(player);
        writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{
        switch (direction) {
        case LEFT:
        	clearPlayer(player);
           	player -= 1;
          	printPlayer(player);
           	waitForButtonRelease(BIT2);
            break;

        case RIGHT:
        	clearPlayer(player);
        	player += 1;
        	printPlayer(player);
        	waitForButtonRelease(BIT1);
        	break;

        case UP:
            clearPlayer(player);
            player -= 0x40;
            printPlayer(player);
            waitForButtonRelease(BIT3);
            break;
          case DOWN:
        	clearPlayer(player);
        	player += 0x40;
        	printPlayer(player);
        	waitForButtonRelease(BIT4);
        	break;

        return player;
}

char didPlayerWin(unsigned char player)
{
        return player == 0xC7;
}
