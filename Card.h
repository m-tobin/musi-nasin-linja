#ifndef CARD_H_
#define CARD_H_

#include <string>

/* Represents a card containing a symbol, which can be rotated by multiples of 90 degrees.
 * Cards are generated at the start of the game and persist throughout, with their pointers stored in decks or boards. */
class Card {

public:
	/* Standard constructor.
	 * cardName initialises name and must be one of:
	 *     "ala", "anu", "en", "jaki", "ken", "li", "nasin" or "pi"
	 * orientation is initialised to 0, and remaining variables are initialised based on this name and orientation.*/
	Card(std::string cardName = "blank");

	std::string getName();
	std::string getImageLine(int line);
	bool getPathGrid(int row, int column);

	/* Rotates the card clockwise by the given number of quarter turns, updating its orientation and symbol.
	 * quarterTurns can be any integer, which will be taken modulo 4.*/
	void rotate(int quarterTurns);

	void printCard(bool border=true);

private:
	std::string name; // card tyoe ("ken", "nasin", "jaki", etc.) or "blank" (used for empty spaces on board)
	int orientation; // between 0 and 3 inclusive

	/* Symbol as an ASCII image 3 characters high and 7 characters wide for printing to user. */
	std::string image[3];

	/* Boolean matrix representing the symbol for internal logic.
	 * true=symbol, false=background */
	bool pathGrid[3][3];
};

#endif /* CARD_H_ */
