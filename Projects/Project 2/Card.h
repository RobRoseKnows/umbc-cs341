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

#include <iostream>
#include <vector>

using namespace std;

#include "Commodity.h"

class Objective;
class Commodity;

class Card {
public:
    void addObjective(Objective* objective);
    Objective* getBestPayoff();
    Objective* getFirstAlphaDestination();
    Objective* getByColor(Commodity::COLOR color);
    void printCard(ofstream& fileStream);
private:
    vector<Objective*> m_objectives;
};

#endif
