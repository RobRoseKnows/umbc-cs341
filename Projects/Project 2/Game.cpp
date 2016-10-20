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
#include<algorithm>

using namespace std;


Game::~Game() {
    while(!m_drawPile.empty()) {
        delete m_drawPile.top();
        m_drawPile.pop();
    }
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

    cerr << "Load cards start." << endl;

    while(!fileIn.eof()) {

        Card* newCard = new Card;

        // Get the string representations of each of the values.
        string dest;
        string commName;
        string payStr;

        fileIn >> dest;
        fileIn >> commName;
        fileIn >> payStr;

        cerr << dest << " " << commName << " " << payStr << endl;

        int pay;
        istringstream(payStr) >> pay;

        cerr << pay << endl;

        Objective* newObjective = createObjective(dest, commName, pay);

        cerr << newObjective->getCommodity()->getName() << " to "
                << newObjective->getDestination() << " for "
                << newObjective->getPayoff() << endl;

        newCard->addObjective(newObjective);

        m_drawPile.push(newCard);

    }

    fileIn.close();

    cerr << "Load cards end." << endl;

}


Objective* Game::createObjective(string dest, string commName, int pay) {

    cerr << "Begin CO" << endl;

    Commodity* commodity = m_bank.getCommodity(commName);

    cerr << commodity->getName();

    return new Objective(dest, commodity, pay);

}
