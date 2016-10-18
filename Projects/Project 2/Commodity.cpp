/*
 * File:    Commodity.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "Commodity.h"
#include <string>

using namespace std;

Commodity::Commodity(string name, string color) {
    m_sName = name;
    m_eColor = resolveColor(color);
}

// Takes a string color name and returns the COLOR type.
Commodity::COLOR Commodity::resolveColor(string color) {

    // Really wish I could use switch statements with strings in C++
    if(color == "Purple") {
        return PURPLE;
    } else if (color == "Red") {
        return RED;
    } else if (color == "Orange") {
        return ORANGE;
    } else if (color == "Black") {
        return BLACK;
    } else if (color == "Green") {
        return GREEN;
    } else if (color == "Brown") {
        return BROWN;
    } else {
        // COLORLESS is the default.
        return COLORLESS;
    }
}
