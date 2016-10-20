#ifndef COMMODITY_H_
#define COMMODITY_H_

/*
 * File:    Commodity.h
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *     The Commodity class header file defines the member variables, the enum type COLOR
 *     and the getters for the values as allowed in the coding style guide. Also contains
 *     the function prototypes for the constructor and the resolveColor function.
 */

#include <string>

using namespace std;

class Commodity {
public:

    // This defines the different colors a commodity can be.
    enum COLOR {
        PURPLE,
        RED,
        ORANGE,
        BLACK,
        GREEN,
        BROWN,
        COLORLESS
    };

    // This is the constructor that resolves the color string inputed and sets
    // m_eColor to it. It does the same for m_sName.
    Commodity(string name, string color);

    string colorToString(COLOR color);

    /* BEGIN DEFINED GETTERS IN HEADER FILE */
    // Getter for color.
    COLOR getColor() const {
        return m_eColor;
    }

    // Returns the name of a commodity
    string getName() const {
        return m_sName;
    }
    /* END DEFINED GETTERS IN HEADER FILE */

private:

    // The name of the commodity.
    string m_sName;

    // The color the commodity is defined as an ENUM.
    COLOR m_eColor;

    /****
     * Name: resolveColor()
     * PreCondition:    No preconditions.
     * PostCondition:   Returns the COLOR ENUM type of a card rather than a string defining the color.
     **/
    COLOR resolveColor(string color);
};

#endif
