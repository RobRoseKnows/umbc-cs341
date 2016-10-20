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
#include <fstream>

using namespace std;

#include "Game.h"
#include "CommodityStore.h"

void printGreeting();

int main(int argc, char ** argv) {
    printGreeting();

    string cardFileName = "";
    string commodFileName = "";
//    string playerFileName = "";
//    string strat = "";

    if(argc >= 2) {
        cardFileName = argv[1];
        commodFileName = argv[2];
//        playerFileName = argv[3];
//        strat = argv[4];
    } else {
        std::cerr << "Not enough arguments." << endl;
        return 1;
    }

    CommodityStore store = CommodityStore();
    Game game = Game();

    store.loadCommodities(commodFileName);
    game.loadCards(cardFileName);

    ofstream fileOut;

    fileOut.open("results.txt", fileOut.out);

    store.printCommodities(fileOut);
    game.printDrawPile(fileOut);

    fileOut.close();

}

void printGreeting() {
    std::cerr << "Robert Rose 3" << endl;
}
