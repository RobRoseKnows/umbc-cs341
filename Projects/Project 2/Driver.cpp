/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#include "Game.h"
#include "Player.h"
#include "CommodityStore.h"

void printGreeting();
void printGreeting(ofstream& out);

int main(int argc, char ** argv) {
    printGreeting();

    string cardFileName;
    string commodFileName;
    string playerNumString;
    string stratString;

//cerr << argc << endl;

    if(argc >= 5){
        cardFileName = argv[1];
        commodFileName = argv[2];
        playerNumString = argv[3];
        stratString = argv[4];
    } else {
        std::cerr << "Not enough arguments." << endl;
        return 1;
    }

    // Conver the strings to ints for number of players and strategy.
    int numPlayers;
    istringstream(playerNumString) >> numPlayers;

    int stratNumber;
    istringstream(stratString) >> stratNumber;
    Player::STRATEGY strat = (Player::STRATEGY) stratNumber;

    // Create game
    Game game = Game();
    CommodityStore* store = game.getBank();

    ofstream fileOut;
    fileOut.open("results.txt", fileOut.out);

    printGreeting(fileOut);

    store->loadCommodities(commodFileName);

    // Play the game.
    game.loadCards(cardFileName);
    game.printDrawPile(fileOut);
    game.runSimulation(numPlayers, strat);
    game.printResults(fileOut);

    fileOut.close();

}

void printGreeting() {
    std::cerr << "Robert Rose, Section 03" << endl;
}

void printGreeting(ofstream& out) {
    out << "Robert Rose, Section 03" << endl;
}
