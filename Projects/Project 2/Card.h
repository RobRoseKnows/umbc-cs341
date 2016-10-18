#ifndef CARD_H_
#define CARD_H_
/*
 * File:    Card.h
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "Commodity.h"

class Objective;
class Commodity;

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

    // Inserts an objective into the card.
    void addObjective(Objective* objective);

    // Returns a pointer to the objective that has the best payoff. Calls the
    // highestPayoffAmong() function.
    Objective* getBestPayoff();

    // Gets the pointer to the objective with first alphabetical name.
    Objective* getFirstAlphaDestination();

    // Returns a pointer to the objective with a commodity whose color matches
    // the requested color. If more than one has that color, return the card
    // with the highest payoff. If none have the color, returns the one with the
    // highest payoff.
    Objective* getByColor(Commodity::COLOR color);

    // This prints the card's objectives.
    void printCard(ofstream& fileStream);
private:
    vector<Objective*> m_objectives;

    // This is the brains behind the getBestPayoff function and other functions
    // that check for the highest payoff. This method checks a vector that's
    // passed in as a parameter.
    Objective* highestPayoffAmong(vector<Objective*> toCheck);
};

#endif
