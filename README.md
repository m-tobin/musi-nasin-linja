# musi-nasin-linja

This is a command-line game adaptation of a simple pen-and-paper game, where two players draw cards from a deck and attempt to join them into a path from the top of their
 board to the bottom, while also creating obstacles which disrupt their opponent's path. It is based around the sitelen pona writing system, used to write the constructed language Toki Pona.
 
 ## Game Rules
 
 ### Intro

Musi nasin linja is a game for two players. Each player receives a board made up of a grid of squares,
 and the aim of the game is to be the first to construct a continuous path from the top of your board to the bottom.
 This is done by placing cards onto the grid, each inscribed with a symbol which can link up with some of the
 surrounding cards.

### Deck and Cards

The deck contains 90 cards of eight different types, each corresponding to a sitelen pona symbol - 
ken (x12), pi (x12), anu (x12), en (x11),  li (x11), nasin (x11), ala (x11) and jaki (x10).
```
* * * * *   * * * * *   * * * * *   * * * * *
*   |__/*   *   |   *   *\_____/*   *   |   *
*   |__ *   *   +---*   *   |   *   *---+---*
*   |  \*   *       *   *   |   *   *   |   *
* * * * *   * * * * *   * * * * *   * * * * *

* * * * *   * * * * *   * * * * *   * * * * *
*\__    *   *   |   *   *\_____/*   *  &~&  *
* __|   *   *  /|\  *   * __|__ *   * &~&~& *
*/      *   *   |   *   */     \*   *  &~&  *
* * * * *   * * * * *   * * * * *   * * * * *
```
The first seven of these are to be placed on your own board to construct a path. The eighth type, \"jaki\",
 does not connect to any of the cards around it, and is to be placed on your opponent's board to disrupt
 their path. At the start of the game, the deck is shuffled and placed face-down, with an empty space for
 the discard pile beside it.

### Gameplay

Players take turns, starting with Player One. On their turn, the player can either draw a card from the
 deck, or pick up the card on top of the discard pile (if there is one). They can then place this card on their
 board. The player can rotate the card to any orientation they wish before placing it, but the symbol on the card
 must either touch the top edge of the top row, or join on to a neighbouring symbol. That is, there must always
 be an unbroken path from the top of the board to the symbol being placed. Once this path touches the bottom edge
 of the bottom row, the player wins the game.
```
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*          |__/                                          
*   #      |__    #      #   -/---\-   #      #      #   
*          |  \              /     \                     
*          |   \_____/\_____/       \_____/\     /       
*   +------+---   |    __|__    #          -\---/---->---
*   |      |      |   /     \                            
```
If the card drawn was a \"jaki\", it can instead be placed anywhere on their opponent's board, so long as there
 is not already a card there. Finally, if the player does not wish to use the card they have drawn, they may place
 it face-up on the discard pile, ending their turn.
 
 ## Credits
 
Created by Max Tobin.

This game is based on the \"musi nasin linja\" pen-and-paper game created by jan Ke Tami for the online
 Toki Pona magazine lipu tenpo: lipu tenpo nanpa pan, p12-13, available at liputenpo.org

The Toki Pona language itself, and its sitelen pona writing system, were created by jan Sonja (Sonja Lang).
