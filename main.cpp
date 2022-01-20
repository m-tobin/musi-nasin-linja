#include "Card.h"
#include "Board.h"

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <cctype>
#include <thread>

void printRules() {
	std::cout << "**************************************************\n\n"

			"INTRO\n\n"

			"MUSI NASIN LINJA is a game for two players. Each player receives a board made up of a grid of squares, "
			"and the aim of the game is to be the first to construct a continuous path from the top of your board to the bottom. "
			"This is done by placing cards onto the grid, each inscribed with a symbol which can link up with some of the "
			"surrounding cards.\n\n"

			"DECK AND CARDS\n\n"

			"The deck contains 90 cards of eight different types, each corresponding to a sitelen pona symbol - "
			"ken (x12), pi (x12), anu (x12), en (x11),  li (x11), nasin (x11), ala (x11) and jaki (x10).\n\n"

			"* * * * *   "  "* * * * *   " "* * * * *   "  "* * * * *\n"
			"*   |__/*   "  "*   |   *   " "*\\_____/*   " "*   |   *\n"
			"*   |__ *   "  "*   +---*   " "*   |   *   "  "*---+---*\n"
			"*   |  \\*   " "*       *   " "*   |   *   "  "*   |   *\n"
			"* * * * *   "  "* * * * *   " "* * * * *   "  "* * * * *\n\n"
			"* * * * *   "  "* * * * *   "  "* * * * *   "  "* * * * *\n"
			"*\\__    *   " "*   |   *   "  "*\\_____/*   " "*  &~&  *\n"
			"* __|   *   "  "*  /|\\  *   " "* __|__ *   "  "* &~&~& *\n"
			"*/      *   "  "*   |   *   "  "*/     \\*   " "*  &~&  *\n"
			"* * * * *   "  "* * * * *   "  "* * * * *   "  "* * * * *\n\n"

			"The first seven of these are to be placed on your own board to construct a path. The eighth type, \"jaki\", "
			"does not connect to any of the cards around it, and is to be placed on your opponent's board to disrupt "
			"their path. At the start of the game, the deck is shuffled and placed face-down, with an empty space for "
			"the discard pile beside it.\n\n"

			"GAMEPLAY\n\n"

			"Players take turns, starting with Player One. On their turn, the player can either draw a card from the "
			"deck, or pick up the card on top of the discard pile (if there is one). They can then place this card on their "
			"board. The player can rotate the card to any orientation they wish before placing it, but the symbol on the card "
			"must either touch the top edge of the top row, or join on to a neighbouring symbol. That is, there must always "
			"be an unbroken path from the top of the board to the symbol being placed. Once this path touches the bottom edge "
			"of the bottom row, the player wins the game.\n\n"

			"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
			"*          |__/                                          \n"
			"*   #      |__    #      #   -/---\\-   #      #      #   \n"
			"*          |  \\              /     \\                     \n"
			"*          |   \\_____/\\_____/       \\_____/\\     /       \n"
			"*   +------+---   |    __|__    #          -\\---/---->---\n"
			"*   |      |      |   /     \\                            \n\n"

			"If the card drawn was a \"jaki\", it can instead be placed anywhere on their opponent's board, so long as there "
			"is not already a card there. Finally, if the player does not wish to use the card they have drawn, they may place "
			"it face-up on the discard pile, ending their turn.\n\n"

			"**************************************************\n\n";
}

void printCredits() {
	std::cout << "**************************************************\n\n"

				"Created by Max Tobin.\n\n"

				"This game is based on the \"musi nasin linja\" pen-and-paper game created by jan Ke Tami for the online "
				"Toki Pona magazine lipu tenpo: lipu tenpo nanpa pan, p12-13, available at liputenpo.org\n\n"

				"The Toki Pona language itself, and its sitelen pona writing system, were created by jan Sonja (Sonja Lang).\n\n"

				"**************************************************\n\n";
}

void printDecks(std::stack<Card*> discardPile, std::stack<Card*> deck) {

	std::string discardPileLine[3];

	if (discardPile.empty()) {
		discardPileLine[0] = "       ";
		discardPileLine[1] = " EMPTY ";
		discardPileLine[2] = "       ";
	}
	else {
		discardPileLine[0] = discardPile.top()->getImageLine(0);
		discardPileLine[1] = discardPile.top()->getImageLine(1);
		discardPileLine[2] = discardPile.top()->getImageLine(2);
	}

	std::cout << " Discard " << "   " << "  Deck   " << "\n";
	std::cout << "* * * * *" << "   " << "* * * * *" << "\n";
	std::cout << "*" << discardPileLine[0] << "*" << "   " << "*" << "       " << "*" << "\n";
	if (deck.size() >= 10) {
		std::cout << "*" << discardPileLine[1] << "*" << "   " << "*" << "  " << deck.size() << "   " << "*" << "\n";
	}
	else {
		std::cout << "*" << discardPileLine[1] << "*" << "   " << "*" << "   " << deck.size() << "   " << "*" << "\n";
	}
	std::cout << "*" << discardPileLine[2] << "*" << "   " << "*" << "       " << "*" << "\n";
	std::cout << "* * * * *" << "   " << "* * * * *" << "\n";

}

void printGameTable(Board playerBoard, Board otherBoard, std::stack<Card*> discardPile, std::stack<Card*> deck) {

	std::cout << "Your board:\n";
	playerBoard.printBoard();
	std::cout << "\n";
	std::cout << "Opponent's board:\n";
	otherBoard.printBoard();
	std::cout << "\n";
	printDecks(discardPile,deck);

}

/* Main interactive loop for a player's turn
 * Throws a char exit code for premature game-overs
 *     F: the player manually forfeit
 *     E: unexpected error (should not occur) */
void takeTurn(Board& playerBoard, Board& otherBoard, std::stack<Card*>& discardPile, std::stack<Card*>& deck) {

	std::string response;
	Card* inHand;

	// Start of turn: show game table status

	printGameTable(playerBoard,otherBoard,discardPile,deck);
	std::cout << "\n--------------------------------------------------\n\n";


	// Draw phase

	if (discardPile.empty() && deck.empty()) {

		// this scenario should not occur. The draw will be checked for at the end of the previous turn.
		throw 'E';

	} else {

		while (true) {

			if (discardPile.empty()) {
				std::cout << "To draw from the deck, enter DRAW.\n";
			} else if (deck.empty()) {
				std::cout << "The deck is empty. To pick up the \"" << discardPile.top()->getName()
						<< "\" from the discard pile, enter PICK UP.\n";
			} else {
				std::cout << "To draw from the deck, enter DRAW.\nTo pick up the \"" << discardPile.top()->getName()
						<< "\" from the discard pile, enter PICK UP.\n";
			}

			// response converted to upper case without whitespace
			std::getline(std::cin,response);
			response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
			std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

			std::cout << "\n";

			if (response.compare("DRAW") == 0 && !deck.empty()) {

				inHand = deck.top();
				deck.pop();
				std::cout << "You drew a(n) \"" << inHand->getName() << "\" from the deck.\n";

			} else if (response.compare("PICKUP") == 0 && !discardPile.empty()) {

				inHand = discardPile.top();
				discardPile.pop();
				std::cout << "You picked up the \"" << inHand->getName() << "\".\n";
				if (discardPile.empty()) {
					std::cout << "The discard pile is now empty.\n";
				} else {
					std::cout << "There is now a(n) \"" << discardPile.top()->getName()
							<< "\" at the top of the discard pile.\n";
				}

			} else {

				std::cout << "Invalid response.\n";
				continue;

			}

			break;

		}
	}

	std::cout << "\n--------------------------------------------------\n\n";


	// Card placement phase

	bool isJaki = (inHand->getName().compare("jaki") == 0);
	bool isTurnOver = false;

	while (!isTurnOver) {

		std::cout << "You are holding a(n) \"" << inHand->getName() << "\":\n";
		inHand->printCard();
		if (isJaki) {
			std::cout << "To place the card on your OPPONENT'S board, enter PLACE.\n";
		} else {
			std::cout << "To place the card on your board, enter PLACE.\n"
						"To rotate the card, enter ROTATE.\n";
		}
		std::cout << "To discard the card, enter DISCARD.\n"
					"To view the boards and decks, enter VIEW.\n"
					"To forfeit the game, enter FORFEIT.\n"
					"For help with the game rules, enter HELP.\n";

		// response converted to upper case without whitespace
		std::getline(std::cin,response);
		response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
		std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

		std::cout << "\n";

		if (response.compare("PLACE") == 0) {

			// inner loop for attempted card placement
			while (true) {

				if (isJaki) {
					std::cout << "Your opponent's board:\n";
					otherBoard.printBoard();
				} else {
					std::cout << "Your board:\n";
					playerBoard.printBoard();
				}
				std::cout << "\n"
							"Enter the coordinates where you would like to place the card.\n"
							"(the letter of the row followed by the number of the column)\n"
							"Or enter BACK to go back.\n";

				// response converted to upper case without whitespace
				std::getline(std::cin,response);
				response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
				std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

				std::cout << "\n";

				if (response.compare("BACK") == 0) {

					break;

				} else if (response.length() >= 2) {

					try {

						// first character interpreted as char A-Z for row
						char rowChar = response[0];
						int row = rowChar-65;

						// remaining string interpreted as integer for column via std::stoi()
						response.erase(0,1);
						int col = std::stoi(response);
							// invalid_argument exception will be thrown for invalid inputs
							// note if the string begins with an integer-convertible substring it is valid and the rest is ignored

						if (row >= 0 && row < Board::height && col >= 0 && col < Board::width) {
							// height is specified to be less than 26, implicitly checks rowChar is upper case A-Z

							if (isJaki) {

								if (otherBoard.insertCard(*inHand,row,col)) {
									std::cout << "You inserted the card at " << rowChar << col << ".\n";
									std::cout << "Your opponent's board:\n";
									otherBoard.printBoard();
									isTurnOver = true;
									break;
								} else {
									std::cout << "You cannot place the card there.\n";
									continue;
								}

							} else {

								if (playerBoard.insertCard(*inHand,row,col)) {
									std::cout << "You inserted the card at " << rowChar << col << ".\n";
									std::cout << "Your board:\n";
									playerBoard.printBoard();
									isTurnOver = true;
									break;
								} else {
									std::cout << "You cannot place the card there.\n";
									continue;
								}

							}

						} else {

							std::cout << "Invalid response.\n";
							continue;

						}

					} catch (const std::invalid_argument& ex) {

						std::cout << "Invalid response.\n";
						continue;

					}

				} else {

					std::cout << "Invalid response.\n";
					continue;

				}


			}

		} else if (response.compare("ROTATE") == 0) {

			// inner loop for attempted rotation
			while (true) {

				std::cout << "Enter a whole number. Your card will rotate that many quarter turns clockwise.\n"
							"Or enter BACK to go back.\n";

				// response converted to upper case without whitespace
				std::getline(std::cin,response);
				response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
				std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

				std::cout << "\n";

				if (response.compare("BACK") == 0) {

					break;

				} else {

					try {

						int turns = std::stoi(response);
							// invalid_argument exception will be thrown for invalid inputs
							// note if the string begins with an integer-convertible substring it is valid and the rest is ignored
						inHand->rotate(turns);
						break;

					} catch (const std::invalid_argument& ex) {

						std::cout << "Invalid response.\n";
						continue;

					}

				}

			}

		} else if (response.compare("DISCARD") == 0) {

			std::cout << "You place the card on the top of the discard pile.\n";
			discardPile.push(inHand);
			isTurnOver = true;

		} else if (response.compare("VIEW") == 0) {

			std::cout << "\n";
			printGameTable(playerBoard,otherBoard,discardPile,deck);
			std::cout << "\n";

		} else if (response.compare("FORFEIT") == 0) {

			std::cout << "Are you sure you want to forfeit? This will end the game.\n"
						"Enter YES to forfeit or press the enter key to go back.\n";

			// response converted to upper case without whitespace
			std::getline(std::cin,response);
			response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
			std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

			std::cout << "\n";

			if (response.compare("YES") == 0) {

				std::cout << "You forfeit the game.\n\n";
				throw 'F';

			} // go back on any input besides "YES"


		} else if (response.compare("HELP") == 0) {

			// specific rules help for card placement

			std::cout << "**************************************************\n\n"

						"You are holding a card in your hand, and to complete your turn you must either place it on a board "
						"or discard it to the top of the discard pile.\n\n";

			if (isJaki) {
				std::cout << "Since the card is a \"jaki\", it goes on your opponent's board. You may place it anywhere "
							"on their board, so long as there is not already a card there. A \"jaki\" cannot be used to form a path, so place it somewhere that will disrupt your "
							"opponent's plans. \n\n"
							"                        &~&  \n"
							" --->------>------>--- &~&~& \n"
							"                        &~&  \n\n";
			} else {
				std::cout << "This card (like all cards except \"jaki\") goes on your own board. Looking at the symbol on the card, you will "
							"see a number of lines which extend outwards towards the edges and/or corners of the square card. These allow "
							"the card to join on to its neighbours.\n\n";
				inHand->printCard();
				std::cout << "\n"
							"You can only place the card at positions on the board where a card has not already been placed, and where it "
							"will either join on to the top of the top row (row A):\n\n"

							"  * * * * * * * * * * * *               * * * * * * * * * * * *\n"
							"  *                                     *          |           \n"
							"A *   #      #      #         ==>     A *   #     \\|/     #    \n"
							"  *                                     *          |           \n\n"

							"Or join on to a card you have already placed:\n\n"

							"                                      |   \n"
							" --->---   #        ==>     --->------+---\n"
							"                                      |   \n\n"

							"In order to do this, you may rotate the card to any orientation you wish before placing it.\n\n";
			}

			std::cout << "**************************************************\n\n";

			std::cout << "To see the full game rules, enter HELP.\n"
						"To go back, press the enter key.\n";

			// response converted to upper case without whitespace
			std::getline(std::cin,response);
			response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
			std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

			std::cout << "\n";

			if (response.compare("HELP") == 0) {
				printRules();
				std::cout << "To go back, press the enter key.\n";
				std::getline(std::cin,response); // accept any input
				std::cout << "\n";
			}

			// go back on any input besides "HELP"

		} else {

			std::cout << "Invalid response.\n";

		}

	}


	// Turn over

	std::cout << "\nPress the enter key to end your turn.\n";
	std::getline(std::cin,response); // accept any input
	std::cout << "\n";

}

int main() {

	std::string response;

	// Welcome

	std::cout << "           "  "        "   "        "  " ______ "  "  ___  "  "\n"
				" O     O   "   "|\\   /| "  "|     | "  "|       "  "   |   "  "\n"
				" |     |   "   "| \\ / | "  "|     | "  "+-----+ "  "   |   "  "\n"
				"  \\___/    "  "|  V  | "   "|_____| "  "______| "  "  _|_  "  "\n"
				"           "   " _      "   "  ___   "   " ______ "  "  ___   "  " _      "  "\n"
				"    |      "   "| \\   | "  " /   \\  "  "|       "  "   |    "  "| \\   |"  "\n"
				"   /|\\     "  "|  \\  | "  "/-----\\ "  "+-----+ "  "   |    "  "|  \\  |"  "\n"
				"    |      "   "|   \\_| "  "|     | "   "______| "  "  _|_   "  "|   \\_|"  "\n"
				"           "    "        "  "  ___   "  " _      "   "   ___  "  "  ___   "  "\n"
				"     __    "    "|       "  "   |    "  "| \\   | "  "    |   "  " /   \\ "  "\n"
				" \\__/  \\   "  "|       "  "   |    "  "|  \\  | "  "    |   "  "/-----\\"  "\n"
				"           "    "|______ "  "  _|_   "  "|   \\_| "  " ___|   "  "|     |"   "\n"
				"\n\n"
				"Welcome!\n\n";

	while (true) {

		std::cout << "To start a new game, enter PLAY.\n"
					"To see the full game rules, enter RULES.\n"
					"To see the credits, enter CREDITS.\n"
					"To exit the game, enter EXIT.\n";

		// response converted to upper case without whitespace
		std::getline(std::cin,response);
		response.erase(std::remove(response.begin(), response.end(), ' '), response.end());
		std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::toupper(c); });

		std::cout << "\n";

		if (response.compare("PLAY") == 0) {

			break;

		} else if (response.compare("RULES") == 0) {

			printRules();
			std::cout << "To go back, press the enter key.\n";
			std::getline(std::cin,response); // accept any input

		} else if (response.compare("CREDITS") == 0) {

			printCredits();
			std::cout << "To go back, press the enter key.\n";
			std::getline(std::cin,response); // accept any input

		} else if (response.compare("EXIT") == 0) {

			return(0);
			std::cout << "\n";

		} else {

			std::cout << "Invalid response.\n";

		}


	}


	// Initialize decks and boards and shuffle the deck

	int numAla = 11;
	int numAnu = 12;
	int numEn = 11;
	int numJaki = 10;
	int numKen = 12;
	int numLi = 11;
	int numNasin = 11;
	int numPi = 12;
	int numCards = numAla + numAnu + numEn + numJaki + numKen + numLi + numNasin + numPi;
	std::vector<Card*> allCards;
	std::stack<Card*> deck;
	std::stack<Card*> discardPile;
	Board playerOneBoard;
	Board playerTwoBoard;

	for (int i=0; i<numAla; i++) {
		Card* newCard = new Card("ala");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numAnu; i++) {
		Card* newCard = new Card("anu");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numEn; i++) {
		Card* newCard = new Card("en");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numJaki; i++) {
		Card* newCard = new Card("jaki");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numKen; i++) {
		Card* newCard = new Card("ken");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numLi; i++) {
		Card* newCard = new Card("li");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numNasin; i++) {
		Card* newCard = new Card("nasin");
		allCards.push_back(newCard);
	}
	for (int i=0; i<numPi; i++) {
		Card* newCard = new Card("pi");
		allCards.push_back(newCard);
	}

	// use current time as seed for Mersenne Twister to shuffle deck pseudo-randomly
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	std::shuffle(allCards.begin(),allCards.end(),gen);

	for (int i=0; i<numCards; i++) {
		deck.push(allCards[i]);
	}


	// Main game loop

	bool playerOneTurn = true;

	while (true) { // breaks when the game is won, drawn or ended early

		// Player turn

		try {
			if (playerOneTurn) {
				std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
							"Player One's Turn\n"
							"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
				takeTurn(playerOneBoard,playerTwoBoard,discardPile,deck);
			} else {
				std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
							"Player Two's Turn\n"
							"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
				takeTurn(playerTwoBoard,playerOneBoard,discardPile,deck);
			}

		} catch (const char& exitCode) { // premature game-overs

			if (exitCode == 'F') { // indicates a forfeit by the player taking their turn

				if (playerOneTurn) {

					std::cout << "**************************************************\n"
								"**************************************************\n"
								"Player Two Wins!\n"
								"**************************************************\n"
								"**************************************************\n";
					break;

				} else {
					std::cout << "**************************************************\n"
								"**************************************************\n"
								"Player One Wins!\n"
								"**************************************************\n"
								"**************************************************\n";
					break;

				}

			} else { // includes exit code 'E' for unexpected errors

				std::cout << "An unexpected error occurred.\n\n"
							"**************************************************\n"
							"**************************************************\n"
							"It's a draw!\n"
							"**************************************************\n"
							"**************************************************\n";
				break;

			}

		}


		// Game-over checks

		if (playerOneBoard.hasWon()) {

			std::cout << "**************************************************\n"
						"**************************************************\n"
						"Player One Wins!\n"
						"**************************************************\n"
						"**************************************************\n";
			break;

		} else if (playerTwoBoard.hasWon()) {

			std::cout << "**************************************************\n"
						"**************************************************\n"
						"Player Two Wins!\n"
						"**************************************************\n"
						"**************************************************\n";
			break;

		} else if (discardPile.empty() && deck.empty()) {

			std::cout << "**************************************************\n"
						"**************************************************\n"
						"It's a draw!\n"
						"**************************************************\n"
						"**************************************************\n"
						"\nThere are no cards left in the deck or discard pile.\n";
			break;

		} else if (playerOneBoard.isBottomRowBlocked() && playerTwoBoard.isBottomRowBlocked()) {

			std::cout << "**************************************************\n"
						"**************************************************\n"
						"It's a draw!\n"
						"**************************************************\n"
						"**************************************************\n"
						"\nBoth players are blocked from reaching the finish line.\n";
			break;

		} else {

			playerOneTurn = !playerOneTurn;

		}

	}


	// End of game screen

	std::cout << "\nPlayer One's board:\n";
	playerOneBoard.printBoard();
	std::cout << "\nPlayer Two's board:\n";
	playerTwoBoard.printBoard();
	std::cout << "\n";
	printDecks(discardPile,deck);
	std::cout << "\n**************************************************\n"
				"**************************************************\n\n"

				"Thanks for playing!\n"
				"Press the enter key to exit the game.\n";

	std::getline(std::cin,response);
	std::cout << "\n";


	// Housekeeping: delete cards created as dynamic objects

	for (int i=0; i<numCards; i++) {
		delete allCards[i];
	}

}
