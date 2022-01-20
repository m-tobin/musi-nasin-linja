#ifndef BOARD_H_
#define BOARD_H_

#include "Card.h"

/* Represents a board containing an 11x11 grid of Cards. */
class Board {

public:
	const static int height = 11; // must be odd (due to board printing format) and less than 26 (alphabetic labels)
	const static int width = 11; // must be odd

	/* Standard constructor.
	 * Board state will be as at the start of the game, filled entirely with "blank" cards.*/
	Board();

	void printBoard();

	/* Checks if a card can be inserted at the given location.
	 * A card can only be inserted if the existing card is a blank, and it is either a jaki or its pathGrid would intersect the nextStepGrid.*/
	bool canInsertCard(Card newCard, int row, int column);

	/* Attempts to insert a card at the given coordinates.
	 * Returns true if the insertion was successful */
	bool insertCard(Card newCard, int row, int column);

	void printPathGrid();
	void printNextStepGrid(); // these two print functions currently used only for debugging

	/* Checks if a player this board belongs to has won the game.
	 * The game is won precisely when there is a true entry in the last row of the pathGrid. */
	bool hasWon();

	/* Checks if every card in the botom row of cards is non-blank.
	 * Used when checking for a draw. */
	bool isBottomRowBlocked();

private:

	Card cards[height][width];

	/* Boolean matrix representing the full current board pattern for internal logic.
	 * This is a combination of the 3x3 pathGrids of each Card on the Board.
	 * true=symbols, false=background */
	bool pathGrid[3*height][3*width];

	/* Boolean matrix used to determine whether a new card joins onto the existing path.
	 * Contains true in:
	 *     all entries in the first row
	 *     entries which are adjacent to an entry from a different card where pathGrid is true
	 * If the entry is in the corner of a card's 3x3 grid, "adjacent" means any of the other 3 entries around that corner.
	 * If the entry is on the edge of a card's 3x3 grid and isn't a corner, "adjacent" means the 1 entry across that edge.*/
	bool nextStepGrid[3*height][3*width];

	/* Updates the nextStepGrid using the current values in the pathGrid. */
	void updateNextStepGrid();

};

#endif /* BOARD_H_ */
