#include "Card.h"

#include <string>
#include <iostream>

Card::Card(std::string cardName /* ="blank" */) {
	name = cardName;
	orientation = 0;
	rotate(0); // initialises image and pathGrid
}

std::string Card::getName() {
	return name;
}

std::string Card::getImageLine(int line) {
	return image[line];
}

bool Card::getPathGrid(int row, int column) {
	return pathGrid[row][column];
}

/* Updates orientation, then updates image and pathGrid to the appropriate form for this name and orientation.
 * Contains hard-coded values for image and pathGrid for each possible card type.*/
void Card::rotate(int quarterTurns) {
	int newOrientation = (orientation + quarterTurns) % 4;

	if (name == "ala") {
		image[0] = "\\_____/";
		image[1] =  " __|__ ";
		image[2] =  "/     \\";
		pathGrid[0][0] = true; pathGrid[0][1] = false; pathGrid[0][2] = true;
		pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
		pathGrid[2][0] = true; pathGrid[2][1] = false; pathGrid[2][2] = true;

	} else if (name == "anu") {
		switch (newOrientation) {
			case 0:
				image[0] = "\\_____/";
				image[1] =  "   |   ";
				image[2] =  "   |   ";
				pathGrid[0][0] = true; pathGrid[0][1] = false; pathGrid[0][2] = true;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = false;
				break;
			case 1:
				image[0] = "    __/";
				image[1] = "---|__ ";
				image[2] = "      \\";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = true;
				pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = true;
				break;
			case 2:
				image[0] =  "   |   ";
				image[1] =  " __|__ ";
				image[2] =  "/     \\";
				pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = true; pathGrid[2][1] = false; pathGrid[2][2] = true;
				break;
			case 3:
				image[0] = "\\__    ";
				image[1] =  " __|---";
				image[2] =  "/      ";
				pathGrid[0][0] = true; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] =false; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = true; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
		}

	} else if (name == "en") {
		image[0] = "   |   ";
		image[1] = "---+---";
		image[2] = "   |   ";
		pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = false;
		pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = true;
		pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = false;

	} else if (name == "jaki") {
			image[0] = "  &~&  ";
			image[1] = " &~&~& ";
			image[2] = "  &~&  ";
			pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
			pathGrid[1][0] = false; pathGrid[1][1] = false; pathGrid[1][2] = false;
			pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;

	} else if (name == "ken") {
		switch (newOrientation) {
			case 0:
				image[0] = "   |__/";
				image[1] = "   |__ ";
				image[2] = "   |  \\";
				pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = true;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = true;
				break;
			case 1:
				image[0] = "       ";
				image[1] = "-/---\\-";
				image[2] = "/     \\";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = true; pathGrid[2][1] = false; pathGrid[2][2] = true;
				break;
			case 2:
				image[0] = "\\__|   ";
				image[1] =  " __|   ";
				image[2] =  "/  |   ";
				pathGrid[0][0] = true; pathGrid[0][1] = true; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = true; pathGrid[2][1] = true; pathGrid[2][2] = false;
				break;
			case 3:
				image[0] = "\\     /";
				image[1] = "-\\---/-";
				image[2] = "       ";
				pathGrid[0][0] = true; pathGrid[0][1] = false; pathGrid[0][2] = true;
				pathGrid[1][0] =true; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
		}

	} else if (name == "li") {
		switch (newOrientation) {
			case 0:
				image[0] = "\\__    ";
				image[1] =  " __|   ";
				image[2] =  "/      ";
				pathGrid[0][0] = true; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] =false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = true; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
			case 1:
				image[0] = "\\_____/";
				image[1] =  "       ";
				image[2] =  "       ";
				pathGrid[0][0] = true; pathGrid[0][1] = false; pathGrid[0][2] = true;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
			case 2:
				image[0] = "    __/";
				image[1] = "   |__ ";
				image[2] = "      \\";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = true;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = true;
				break;
			case 3:
				image[0] =  "       ";
				image[1] =  " _____ ";
				image[2] =  "/     \\";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = true; pathGrid[2][1] = false; pathGrid[2][2] = true;
				break;
		}

	} else if (name == "nasin") {
		switch (newOrientation) {
			case 0:
				image[0] = "   |   ";
				image[1] = "  /|\\  ";
				image[2] = "   |   ";
				pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = false;
				break;
			case 1:
				image[0] = "       ";
				image[1] = "--->---";
				image[2] = "       ";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
			case 2:
				image[0] =  "   |   ";
				image[1] = "  \\|/  ";
				image[2] =  "   |   ";
				pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = false;
				break;
			case 3:
				image[0] = "       ";
				image[1] = "---<---";
				image[2] = "       ";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
		}

	} else if (name == "pi") {
		switch (newOrientation) {
			case 0:
				image[0] = "   |   ";
				image[1] = "   +---";
				image[2] = "       ";
				pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
			case 1:
				image[0] = "       ";
				image[1] = "   +---";
				image[2] = "   |   ";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] = false; pathGrid[1][1] = true; pathGrid[1][2] = true;
				pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = false;
				break;
			case 2:
				image[0] = "       ";
				image[1] = "---+   ";
				image[2] = "   |   ";
				pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
				pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = true; pathGrid[2][2] = false;
				break;
			case 3:
				image[0] = "   |   ";
				image[1] = "---+   ";
				image[2] = "       ";
				pathGrid[0][0] = false; pathGrid[0][1] = true; pathGrid[0][2] = false;
				pathGrid[1][0] = true; pathGrid[1][1] = true; pathGrid[1][2] = false;
				pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;
				break;
		}

	} else { // name == "blank"
		image[0] = "       ";
		image[1] = "   #   ";
		image[2] = "       ";
		pathGrid[0][0] = false; pathGrid[0][1] = false; pathGrid[0][2] = false;
		pathGrid[1][0] = false; pathGrid[1][1] = false; pathGrid[1][2] = false;
		pathGrid[2][0] = false; pathGrid[2][1] = false; pathGrid[2][2] = false;

	}

	orientation = newOrientation;

}

void Card::printCard(bool border /* =true */) {
	if (border) {
		std::cout << "* * * * *\n";
		std::cout << "*" << image[0] << "*\n*" << image[1] << "*\n*" << image[2] << "*\n";
		std::cout << "* * * * *\n";
	} else {
		std::cout << image[0] << "\n" << image[1] << "\n" << image[2] << "\n";
	}
}
