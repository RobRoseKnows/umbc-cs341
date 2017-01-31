/*
 * File:    Commodity.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *     This is the code for the Commodity class. Because I defined the getters in the header file,
 *     this only has the constructor and the resolveColor() function.
 */

#include "Commodity.h"
#include <string>

using namespace std;

Commodity::Commodity(string name, string color) {

    m_sName = name;
    m_eColor = resolveColor(color);

}

// resolveColor
// takes a string color value and returns to a COLOR type.
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

string Commodity::colorToString(COLOR color) {
    switch(color) {
        case PURPLE:
            return "Purple";
        case RED:
            return "Red";
        case ORANGE:
            return "Orange";
        case BLACK:
            return "Black";
        case GREEN:
            return "Green";
        case BROWN:
            return "Brown";
        case COLORLESS:
            return "Colorless";
        default:
            return "ERROR NOT A VALID COLOR";
    }
}
