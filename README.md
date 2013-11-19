LCD-Game
========

In this game, the player will be represented by an asterisk (*), starting in the top left corner of the screen. 
By using push buttons, the player advances through the board. The goal of the player is to make it to the 
bottom right corner of the screen.

 PB1=right
 PB2=left
 PB3=up 
 PB4=down
 
 If the player doesn't move within 2 seconds, the game ends - display "GAME" on the first line and "OVER!" 
 on the second line. If the player reaches the bottom right corner of the screen, they won - display "YOU" 
 on the first line" and "WON!" on the second line. At this point, pushing any of the buttons 
 should initiate a new game.
 
 Interrupt  was used for the button presses.
 The player does not go beyond the borders (off screen)
 
 Documentation:
 C2C Schriner explained the logic behind interrupts and how to use them
 C2C Busho explained how to use SWITCH 
 Used Captain Branchflower's Buttons, LCD, game skeleton
