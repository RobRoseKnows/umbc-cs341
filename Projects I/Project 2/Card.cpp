/*
 *  File:    Driver.cpp
 *  Author:  Robert Rose
 *  Section: 3
 *  Created: 10/11/16
 *  E-mail:  robrose2@umbc.edu
 *  Description:
 *      This class holds the Card object that allows the rest of the program to print cards,
 *      or find the best card for a certain strategy.
 */

#include "Objective.h"
#include "Player.h"
#include "Commodity.h"
#include "Card.h"


#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Card::Card() { /* Empty constructor */  }

Card::~Card() {
    while(!m_objectives.empty()) {

        // pop_back() apparently doesn't return any values so we have to delete the
        // the last item before we pop it out of the array.
        delete m_objectives[m_objectives.size() - 1];
        m_objectives.pop_back();

    }
}


Objective* Card::getFromStrategy(Player::STRATEGY strat) {
    switch(strat) {
        case Player::BEST_PAYOFF:
            return getBestPayoff();

        case Player::FIRST_DESTINATION:
            return getFirstAlphaDestination();

        case Player::COLOR_PURPLE:
            return getByColor(Commodity::PURPLE);

        case Player::COLOR_RED:
            return getByColor(Commodity::RED);

        case Player::COLOR_ORANGE:
            return getByColor(Commodity::ORANGE);

        case Player::COLOR_BLACK:
            return getByColor(Commodity::BLACK);

        case Player::COLOR_GREEN:
            return getByColor(Commodity::GREEN);

        case Player::COLOR_BROWN:
            return getByColor(Commodity::BROWN);

        default:
            cerr << "Not a valid strategy";
            return getBestPayoff();
    }
}


/****
 * Name: addObjective()
 * PreCondition:    No preconditions required.
 * PostCondition:   Adds one more objective to the back of the m_objectives vector.
 **/
void Card::addObjective(Objective* objective) {
//    cerr << "added objective" << endl;
    m_objectives.push_back(objective);
}



/****
 * Name: getBestPayoff()
 * PreCondition:    In order to actually return something, there must be at least
 *                  one objective in the m_objectives vector. Otherwise it will
 *                  throw a CardException.
 * PostCondition:   Returns the pointer to the objective with the highest payoff.
 **/
Objective* Card::getBestPayoff() {

    // We aren't guaranteed to have any objectives in the card. This is just in case.
    if(m_objectives.size() <= 0)
        { throw CardException("No objectives in card."); }

    // I moved the code for this to a separate function so that I could use the same function
    // to find the highest payoff among other card vectors.
    return highestPayoffAmong(m_objectives);

}



/****
 * Name: getFirstAlphaDestination()
 * PreCondition:    In order to actually return something, there must be at least
 *                  one objective in the m_objectives vector. Otherwise it will
 *                  throw a runtime exception.
 * PostCondition:   Returns the pointer to the objective with the destination with
 *                  the highest name alphabetically.
 **/
Objective* Card::getFirstAlphaDestination() {

    // We aren't guaranteed to have any objectives in the card. This is just in case.
    if(m_objectives.size() <= 0)
        { throw CardException("No objectives in card."); }

    Objective* firstObj = m_objectives[0];
    string firstName = firstObj->getDestination();

    for(vector<Objective*>::size_type i = 0; i < m_objectives.size(); i++) {

        Objective* on = m_objectives[i];

        // Use less than in order to hold the oldest one on the card.
        if(on->getDestination().compare(firstName) < 0) {

            firstObj = on;
            firstName = firstObj->getDestination();

        }

    }

    return firstObj;
}



// Returns a pointer to the objective with a commodity whose color matches
// the requested color. If more than one has that color, return the card
// with the highest payoff. If none have the color, returns the one with the
// highest payoff.
Objective* Card::getByColor(Commodity::COLOR color) {

    // We aren't guaranteed to have any objectives in the card. This is just in case.
    if(m_objectives.size() <= 0)
        { throw CardException("No objectives in card."); }

    Objective* toReturn;
    vector<Objective*> allWithColor;

    // Using size_type is apparently best practices for C++.
    for(vector<Objective*>::size_type i = 0; i < m_objectives.size(); i++) {

        Objective* on = m_objectives[i];

        // Add all the cards of the color to another vector.
        if(on->getCommodity()->getColor() == color) {

            allWithColor.push_back(on);

        }
//        on = NULL;
    }

    if(allWithColor.size() > 0) {

        // Then find the highest payoff among those cards.
        toReturn = highestPayoffAmong(allWithColor);

    } else {

        toReturn = getBestPayoff();

    }

    // TODO: Don't know if I need to do this, will get back to you.
//    delete allWithColor;

    return toReturn;
}



/****
 * Name: printCard()
 * PreCondition:    No precondition but it won't be much help unless the card has
 *                  some objectives.
 * PostCondition:   Prints a header for the card and then prints each objective in
 *                  order of when they were added to the card.
 **/
void Card::printCard(ofstream& fileStream) {

    fileStream << "---------- CARD ----------" << endl;

    // Make sure to use size_type!
    for(vector<Objective*>::size_type i = 0; i < m_objectives.size(); i++) {

        m_objectives[i]->printObjective(fileStream);

    }

    fileStream << "--------------------------" << endl;

}



// This is the brains behind the getBestPayoff function and other functions
// that check for the highest payoff. This method checks a vector that's
// passed in as a parameter.
Objective* Card::highestPayoffAmong(vector<Objective*> toCheck) {
    if(toCheck.size() <= 0)
        { throw CardException("Weren't enough objectives in the vector to check."); }

    Objective* maxObj = toCheck[0];
    int maxPayoff = maxObj->getPayoff();

    for(vector<Objective*>::size_type i = 0; i < toCheck.size(); i++) {

        // Having a greater than sign here makes sure we will always have the
        // first objective to be added as that's what the project description
        // calls for if there's more than one with a max payoff.
        if(toCheck[i]->getPayoff() > maxPayoff) {
            maxObj = toCheck[i];
            maxPayoff = maxObj->getPayoff();
        }
    }

    return maxObj;
}
