/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "Player.h"
#include "Card.h"
#include "Objective.h"
#include <iostream>


using namespace std;



Player::Player(string name) {
    m_sName = name;
}



Player::~Player() {
    while(!m_cards.empty()) {
        delete m_cards.front();
        m_cards.pop();
    }

    while(!m_objectives.empty()) {
        delete m_objectives.front();
        m_objectives.pop();
    }
}


// Takes a card and adds it to the m_cards queue.
void Player::addCard(Card* card) {
//    cerr << m_sName << " added card." << endl;
    m_cards.push(card);
}



int Player::getScore() const {
    int score = 0;

    queue<Objective*> objectivesCopy = m_objectives;

    while(!objectivesCopy.empty()) {
//        cerr << "getting score " << objectivesCopy.size() << endl;
        score += objectivesCopy.front()->getPayoff();
        objectivesCopy.pop();
    }

    return score;
}



int Player::calculateScore(STRATEGY strategy) {
    queue<Card*> cardCopy = m_cards;

    // This is for if we've already chosen the best Objectives, we don't want
    // to do it again.
    if(!m_objectives.empty()) {
        return getScore();
    }

    while(!cardCopy.empty()) {

//        cerr << "calc score " << cardCopy.size() << endl;

        Card* card = cardCopy.front();
        m_objectives.push(card->getFromStrategy(strategy));
        cardCopy.pop();

    }

    return getScore();
}


// This prints the results of the game.
void Player::printResult(ofstream & fileStream) {

    fileStream << "--------" << m_sName << "------------" << endl;

    // Create a duplicate of the objectives queue so we can move through it.
    queue<Objective*> objectivesCopy = m_objectives;

    while(!objectivesCopy.empty()) {
        Objective* obj = objectivesCopy.front();
        obj->printObjective(fileStream);
        objectivesCopy.pop();
    }

    fileStream << "Score: " << getScore() << endl;
}


// Given a strategy, it returns a string.
string Player::strategyToString(STRATEGY strat) {
    switch(strat) {
        case BEST_PAYOFF:
            return "Best Payoff";
        case FIRST_DESTINATION:
            return "First Destination";
        case COLOR_PURPLE:
            return "Color Purple";
        case COLOR_RED:
            return "Color Red";
        case COLOR_ORANGE:
            return "Color Orange";
        case COLOR_BLACK:
            return "Color Black";
        case COLOR_GREEN:
            return "Color Green";
        case COLOR_BROWN:
            return "Color Brown";
        default:
            return "ERROR: NOT A VALID STRATEGY";
    }
}
