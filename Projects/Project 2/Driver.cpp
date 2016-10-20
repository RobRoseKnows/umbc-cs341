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
void printGreeting(ofstream& out);

int main(int argc, char ** argv) {
    printGreeting();

    string cardFileName = "";
    string commodFileName = "";
//    string playerFileName = "";
//    string strat = "";

//cerr << argc << endl;

    if(argc >= 3){
        cardFileName = argv[1];
        commodFileName = argv[2];
//        playerFileName = argv[3];
//        strat = argv[4];
    } else {
        std::cerr << "Not enough arguments." << endl;
        return 1;
    }

    Game game = Game();
    CommodityStore* store = game.getBank();


    ofstream fileOut;

    fileOut.open("results.txt", fileOut.out);

    printGreeting(fileOut);

    store->loadCommodities(commodFileName);
//    store->printCommodities(fileOut);

    game.loadCards(cardFileName);
    game.printDrawPile(fileOut);

    fileOut.close();

}

void printGreeting() {
    std::cerr << "Robert Rose, Section 03" << endl;
}

void printGreeting(ofstream& out) {
    out << "Robert Rose, Section 03" << endl;
}
