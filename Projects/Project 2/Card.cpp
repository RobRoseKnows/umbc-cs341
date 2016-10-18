/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "Card.h"
#include "Objective.h"

#include <fstream>
#include <vector>
#include <string>

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

// Add the new objective to the back of the vector.
void Card::addObjective(Objective* objective) {
    m_objectives.push_back(objective);
}

Objective* Card::getBestPayoff() {
    // We aren't guaranteed to have any objectives in the card. This is just in case.
    if(m_objectives.size() <= 0)
        throw CardException("No objectives in card.");

    return highestPayoffAmong(m_objectives);
}

Objective* Card::getFirstAlphaDestination() {
    // We aren't guaranteed to have any objectives in the card. This is just in case.
    if(m_objectives.size() <= 0)
        throw CardException("No objectives in card.");

    Objective* firstObj = m_objectives[0];
    string firstName = firstObj->getDestination();
}

Objective* Card::getByColor(Commodity::COLOR color) {
    // We aren't guaranteed to have any objectives in the card. This is just in case.
    if(m_objectives.size() <= 0)
        throw CardException("No objectives in card.");

    Objective* toReturn;
    vector<Objective*> allWithColor;

    // Using size_type is apparently best practices for C++.
    for(vector<Objective*>::size_type i = 0; i < m_objectives.size(); i++) {
        Objective* on = m_objectives[i];
        if(on->getCommodity()->getColor() == color) {
            allWithColor.push_back(on);
        }.
//        on = NULL;
    }

    if(allWithColor.size() > 0) {
        toReturn = highestPayoffAmong(allWithColor);
    } else {
        toReturn = getBestPayoff();
    }

    // TODO: Don't know if I need to do this, will get back to you.
//    delete allWithColor;

    return toReturn;
}

// Print the cards out in the order in which they were received.
void Card::printCard(ofstream& fileStream) {
    fileStream << "---------- CARD ----------" << endl;

    // Make sure to use size_type!
    for(vector<Objective*>::size_type i = 0; i < m_objectives.size(); i++) {
        m_objectives[i]->printObjective(fileStream);
    }
}

Objective* Card::highestPayoffAmong(vector<Objective*> toCheck) {
    if(toCheck.size() <= 0)
        throw CardException("Weren't enough objectives in the vector to check.");

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
