#include "Board.h"

#include "Card.h"

#include <iostream>

Board::Board() {
	// cards is automatically initialised with default Card constructor (i.e. all blank)
	for (int i=0; i<3*height; i++) {
		for (int j=0; j<3*width; j++) {
			pathGrid[i][j] = false;
			nextStepGrid[i][j] = false;
		}
	}
	updateNextStepGrid();
}

/* Iterates over each set of 3 rows in the pathGrid corresponding to a row of cards, and over each entry in these rows (broken down by
 * position in the 3x3 grid blocks representing individual cards), updating the adjacent entries in nextStepGrid.
 * Note that there will be many unnecessary true values in locations where cards have already been placed, but this has no effect since
 * we only check the nextStepGrid after checking the card in a given location is blank.*/
void Board::updateNextStepGrid() {

	// starting row
	for (int j=0; j<3*width; j++) {
		nextStepGrid[0][j] = true;
	}

	for (int i=0; i<3*height; i=i+3) {

		// for corners of cards (top-lefts, top-rights, bottom-lefts, bottom-rights) where pathGrid=true, update the 3 adjacent entries
		// around the corner
		// for non-corner edges (top-middles, centre-lefts, centre-rights, bottom-middles) where pathGrid=true update the 1 adjacent entry
		// across the edge
		// in all cases most of the logic comes from boundary checking

		// check top-lefts
		for (int j=0; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (i>0) {
					nextStepGrid[i-1][j] = true;
					if (j>0) {
						nextStepGrid[i][j-1] = true;
						nextStepGrid[i-1][j-1] = true;
					}
				} else if (j>0) {
					nextStepGrid[i][j-1] = true;
				}
			}
		}

		// check top-middles
		for (int j=1; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (i>0) {
					nextStepGrid[i-1][j] = true;
				}
			}
		}

		// check top-rights
		for (int j=2; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (i>0) {
					nextStepGrid[i-1][j] = true;
					if (j<3*width-1) {
						nextStepGrid[i][j+1] = true;
						nextStepGrid[i-1][j+1] = true;
					}
				} else if (j<3*width-1) {
					nextStepGrid[i][j+1] = true;
				}
			}
		}
	}

	for (int i=1; i<3*height; i=i+3) {

		// check centre-lefts
		for (int j=0; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (j>0) {
					nextStepGrid[i][j-1] = true;
				}
			}
		}

		// note we do not need to check centre-middles

		// check centre-rights
		for (int j=2; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (j<3*width-1) {
					nextStepGrid[i][j+1] = true;
				}
			}
		}
	}

	for (int i=2; i<3*height; i=i+3) {

		// check bottom-lefts
		for (int j=0; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (i<3*height-1) {
					nextStepGrid[i+1][j] = true;
					if (j>0) {
						nextStepGrid[i][j-1] = true;
						nextStepGrid[i+1][j-1] = true;
					}
				} else if (j>0) {
					nextStepGrid[i][j-1] = true;
				}
			}
		}

		// check bottom-middles
		for (int j=1; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (i<3*height-1) {
					nextStepGrid[i+1][j] = true;
				}
			}
		}

		// check bottom-rights
		for (int j=2; j<3*width; j=j+3) {
			if (pathGrid[i][j]) {
				if (i<3*height-1) {
					nextStepGrid[i+1][j] = true;
					if (j<3*width-1) {
						nextStepGrid[i][j+1] = true;
						nextStepGrid[i+1][j+1] = true;
					}
				} else if (j<3*width-1) {
					nextStepGrid[i][j+1] = true;
				}
			}
		}
	}
}

void Board::printBoard() {

	char rowLabel = 'A';
	int columnLabel = 0;

	// numeric labels for columns printed along the top of the board
	std::cout << "    ";
	for (int i=0; i<width; i++) {
		std::cout << "   " << columnLabel << "   ";
		columnLabel++;
	}
	std::cout << "\n";

	// top row of asterisks
	std::cout << "   *";
	for (int i=0; i<(width-1)/2; i++) {
		std::cout << " * * * * * * *";
	}
	std::cout << " * * * *\n";

	// rows of card images with alphabetic labels at the left (centered vertically)
	for (int i=0; i<height; i++) {
		for (int j=0; j<3; j++) {
			if (j==1) {
				std::cout << " " << rowLabel << " ";
				rowLabel++;
			} else {
				std::cout << "   ";
			}
			std::cout << "*";
			for (int k=0; k<width; k++) {
				std::cout << cards[i][k].getImageLine(j);
			}
			std::cout << "*";
			std::cout << "\n";
		}
	}

	// bottom row of asterisks
	std::cout << "   *";
	for (int i=0; i<(width-1)/2; i++) {
		std::cout << " * * * * * * *";
	}
	std::cout << " * * * *\n";

}

void Board::printPathGrid() {
	for (int i=0; i<3*height; i++) {
		std::cout << " ";
		for (int j=0; j<3*width; j++) {
			std::cout << pathGrid[i][j];
		}
		std::cout << " \n";
	}
}

void Board::printNextStepGrid() {
	for (int i=0; i<3*height; i++) {
		std::cout << " ";
		for (int j=0; j<3*width; j++) {
			std::cout << nextStepGrid[i][j];
		}
		std::cout << " \n";
	}
}

bool Board::canInsertCard(Card newCard, int row, int column) {
	if (cards[row][column].getName().compare("blank") != 0) {
		return false;
	}
	if (newCard.getName().compare("jaki") == 0) {
		return true;
	}
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (newCard.getPathGrid(i,j) && nextStepGrid[3*row+i][3*column+j]) {
				return true;
			}
		}
	}
	return false;
}

bool Board::insertCard(Card newCard, int row, int column) {
	if (canInsertCard(newCard,row,column)) {
		cards[row][column] = newCard;
		for (int i=0; i<3; i++) {
			for (int j=0; j<3; j++) {
				pathGrid[3*row+i][3*column+j] = newCard.getPathGrid(i,j);
			}
		}
		updateNextStepGrid();
		return true;
	} else {
		return false;
	}
}

bool Board::hasWon() {
	for (int i=0; i<3*width; i++) {
		if (pathGrid[3*height-1][i]) {
			return true;
		}
	}
	return false;
}

bool Board::isBottomRowBlocked() {
	for (int i=0; i<width; i++) {
		if (cards[height-1][i].getName().compare("blank") == 0) {
			return false;
		}
	}
	return true;
}

