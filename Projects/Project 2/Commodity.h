#ifndef COMMODITY_H_
#define COOMODITY_H_

/*
 * File:    Commodity.h
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

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
    ~Commodity();


    string getName() const;
    COLOR getColor() const;

private:
    string m_sName;
    string m_eColor;

    COLOR resolveColor(string color);
};

#endif
