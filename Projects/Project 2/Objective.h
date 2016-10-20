#ifndef OBJECTIVE_H_
#define OBJECTIVE_H_
/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include<fstream>

using namespace std;

class Commodity;

class Objective {
public:
    // Constructor that takes destination, commodity and payoff.
    Objective(string dest, Commodity* comm, int pay);
    // Deconstructor
    ~Objective();

    // Prints the objective to an ofsteam.
    // Prints in the format: "<commodity> to <destination> for <payoff>"
    void printObjective(ofstream & fileStream);


    /* Implement Getters in the header file */
    // Return the destination.
    string getDestination() const {
        return m_sDestination;
    }

    // Returns the pointer to a commodity.
    Commodity* getCommodity() const {
        return m_pCommodity;
    }

    // Returns the payoff for this objective.
    int getPayoff() const {
        return m_iPayoff;
    }
private:
    string m_sDestination;
    Commodity* m_pCommodity;
    int m_iPayoff;
};
#endif
