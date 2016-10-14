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

#include<iostream>

using namespace std;

class Commodity;

class Objective {
public:
    string getDestination() const;
    Commodity* getCommodity() const;
    int getPayoff() const;
    void printObjective(ofstream & fileStream);
};
#endif
