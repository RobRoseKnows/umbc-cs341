#ifndef COMMODITY_H_
#define COMMODITY_H_

/*
 * File:    Commodity.h
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include <string>

using namespace std;

class Commodity {
public:
    enum COLOR {
        PURPLE,
        RED,
        ORANGE,
        BLACK,
        GREEN,
        BROWN,
        COLORLESS
    };

    Commodity(string name, string color);


    /* Defined getters in header file. */
    // Getter for color.
    COLOR getColor() const {
        return m_eColor;
    }

    // Returns the name of a commodity
    string getName() const {
        return m_sName;
    }

private:
    string m_sName;
    COLOR m_eColor;

    COLOR resolveColor(string color);
};

#endif
