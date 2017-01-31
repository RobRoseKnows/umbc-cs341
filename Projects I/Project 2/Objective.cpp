/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 *
 */

#include "Objective.h"
#include "Commodity.h"

#include <ostream>

using namespace std;

Objective::Objective(string dest, Commodity* comm, int pay) {
    m_sDestination = dest;
    m_pCommodity = comm;
    m_iPayoff = pay;
}

// Delete the dynamic memory.
Objective::~Objective() {
    m_pCommodity = NULL;
}

// Prints the objective out to the ofstream.
// Prints in the format: "<commodity> to <destination> for <payoff>"
void Objective::printObjective(ofstream & fileStream) {
    fileStream << m_pCommodity->getName() << " to " << m_sDestination << " for " << m_iPayoff << endl;
}
