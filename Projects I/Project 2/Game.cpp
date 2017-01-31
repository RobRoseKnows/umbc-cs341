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
#include<string>
#include<fstream>
#include<sstream>
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

    while(!m_players.empty()) {
        delete m_players.back();
        m_players.pop_back();
    }

    delete m_bank;
}


void Game::runSimulation(int players, Player::STRATEGY strategy) {

    for(int i = 1; i <= players; i++) {
        ostringstream playerNameStream;
        playerNameStream << "Player " << i;

        Player* newPlayer = new Player(playerNameStream.str());
        m_players.push_back(newPlayer);
    }


    // This is tells us how many cards are left after each player has an equal amount of cards.
    int cardsLeft = m_drawPile.size() % players;

    stack<Card*> drawPileCopy = m_drawPile;

    // Index of the player you're currently drawing for.
    int playerOn = 0;


    while(!drawPileCopy.empty()) {

//        cerr << "Draw size: " << drawPileCopy.size() << endl;

        // If we're on our last few cards, don't draw them.
        if(drawPileCopy.size() <= cardsLeft) {
            break;
        }

        Card* top = drawPileCopy.top();

        m_players[playerOn]->addCard(top);

        drawPileCopy.pop();

        playerOn++;
        if(playerOn >= players) {
            playerOn = 0;
        }
    }

    for(int i = 0; i < m_players.size(); i++) {
        m_players[i]->calculateScore(strategy);
    }

//    cerr << "Done." << endl;

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

    fileStream << "---------- RESULTS ----------" << endl;

    string winner;
    int maxScore = 0;
    for(int i = 0; i < m_players.size(); i++) {
        m_players[i]->printResult(fileStream);

        // Used for finding the winner. Saves on making another loop.
        if(m_players[i]->getScore() > maxScore) {
            winner = m_players[i]->getName();
            maxScore = m_players[i]->getScore();
        }
    }


    fileStream << "--------------------------" << endl;

    // Find the winner.


    fileStream << "Winner: " << winner << " Score: " << maxScore << endl;

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

            // Conver the string to an int.
            int pay;
            istringstream(payStr) >> pay;

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
