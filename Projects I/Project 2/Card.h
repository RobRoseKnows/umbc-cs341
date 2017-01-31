#ifndef CARD_H_
#define CARD_H_
/*
 *  File:    Card.h
 *  Author:  Robert Rose
 *  Section: 3
 *  Created: 10/11/16
 *  E-mail:  robrose2@umbc.edu
 *  Description:
 *      This is the class header file for the Card class. It defines function protypes and
 *      member variables as well as an Exception that can be thrown by the Card class.
 */

#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

#include "Objective.h"
#include "Commodity.h"
#include "Player.h"

class Objective;
class Commodity;
class Player;

// This is thrown if there are any exceptions while running in the Card class.
class CardException : public std::runtime_error {

   public:

    CardException(const string& what) : std::runtime_error(what) { }

} ;

class Card {
public:

    Card();

    // Deconstructer that deletes all the objectives in the m_objectives pointer.
    ~Card();

    /****
     * Name: addObjective()
     * PreCondition:    No preconditions required.
     * PostCondition:   Adds one more objective to the m_objectives vector.
     **/
    void addObjective(Objective* objective);

    /****
     * Name: getBestPayoff()
     * PreCondition:    In order to actually return something, there must be at least
     *                  one objective in the m_objectives vector. Otherwise it will
     *                  throw a CardException.
     * PostCondition:   Returns the pointer to the objective with the highest payoff.
     **/
    Objective* getBestPayoff();

    /****
     * Name: getFirstAlphaDestination()
     * PreCondition:    In order to actually return something, there must be at least one
     *                  objective in the m_objectives vector. Otherwise it will throw a
     *                  CardException.
     * PostCondition:   Returns the pointer to the objective with the destination with
     *                  the highest name alphabetically.
     **/
    Objective* getFirstAlphaDestination();

    // Returns a pointer to the objective with a commodity whose color matches
    // the requested color. If more than one has that color, return the card
    // with the highest payoff. If none have the color, returns the one with the
    // highest payoff.
    Objective* getByColor(Commodity::COLOR color);


    Objective* getFromStrategy(Player::STRATEGY strat);

    /****
     * Name: printCard()
     * PreCondition:    No precondition but it won't be much help unless the card has
     *                  some objectives.
     * PostCondition:   Prints a header for the card and then prints each objective in
     *                  order of when they were added to the card.
     **/
    void printCard(ofstream& fileStream);
private:
    vector<Objective*> m_objectives;

    // This is the brains behind the getBestPayoff function and other functions
    // that check for the highest payoff. This method checks a vector that's
    // passed in as a parameter.
    Objective* highestPayoffAmong(vector<Objective*> toCheck);

};

#endif
