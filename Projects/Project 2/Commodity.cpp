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

using namespace std;

Commodity::Commodity(string name, string color) {
    m_sName = name;

}

Commodity::~Commodity() {

}

Commodity::COLOR Commodity::getColor() const {
    return m_eColor;
}

string Commodity::getName() const {
    return m_sName;
}

Commodity::COLOR Commodity::resolveColor(string color) {

}
