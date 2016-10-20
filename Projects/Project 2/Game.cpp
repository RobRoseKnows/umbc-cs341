/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "Game.h"
#include<fstream>
#include<sstream>
#include<istream>
#include<iterator>

using namespace std;

Game::Game() {
    m_bank = new CommodityStore();
}


Game::~Game() {
    while(!m_drawPile.empty()) {
        delete m_drawPile.top();
        m_drawPile.pop();
    }

    delete m_bank;
}


void Game::runSimulation(int players, Player::STRATEGY strategy) {

}



void Game::printDrawPile(ofstream& fileStream) {

    fileStream << "---------- Draw Pile ----------" << endl;

    stack<Card*> drawPileCopy = m_drawPile;

    while(!drawPileCopy.empty()) {

        Card* top = drawPileCopy.top();
        drawPileCopy.pop();

        top->printCard(fileStream);

    }
}



void Game::printResults(ofstream& fileStream) {

}



void Game::loadCards(string filename) {

    ifstream fileIn;
    fileIn.open(filename.c_str(), fileIn.in);

//    cerr << "Load cards start." << endl;

    while(!fileIn.eof()) {
        Card* newCard = new Card;

        // Apparently we're guranteed there will always be 3.
        for(int i = 0; i < 3; i++) {
            // Get the string representations of each of the values.
            string dest;
            string commName;
            string payStr;

            // Read in the values from the file.
            fileIn >> dest;
            fileIn >> commName;
            fileIn >> payStr;

            // This gets rid of the problems we have with the last blank lines.
            if(dest == "") {
                fileIn.close();
                delete newCard;
                return;
            }

            //        cerr << dest << " " << commName << " " << payStr << endl;

            int pay;
            istringstream(payStr) >> pay;

            //        cerr << pay << endl;

            Objective* newObjective = createObjective(dest, commName, pay);

//            cerr << newObjective->getCommodity()->getName() << " to "
//                    << newObjective->getDestination() << " for "
//                    << newObjective->getPayoff() << endl;

            newCard->addObjective(newObjective);
        }

        m_drawPile.push(newCard);

    }

    fileIn.close();

    cerr << "Load cards end." << endl;

}


Objective* Game::createObjective(string dest, string commName, int pay) {

//    cerr << "Begin CO" << endl;

    Commodity* commodity = m_bank->getCommodity(commName);

//    cerr << commodity->getName() << endl;

    return new Objective(dest, commodity, pay);

}
