/*
 * File:    CommodityStore.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *      CommodityStore.cpp contains the code for the CommodityStore class. This class
 *      contains a map for each of the Commodity objects.
 */

#include "CommodityStore.h"

#include<fstream>
#include<istream>
#include<iostream>
#include<stdexcept>

using namespace std;


CommodityStore::~CommodityStore() {

    // Special thanks: http://stackoverflow.com/a/4844904/1021259 for this line:
    typedef map<string, Commodity*>::iterator it_type;

    for(it_type itr = m_store.begin(); itr != m_store.end(); itr++) {

        // I originally had it deleting the itr->second but that didn't work so now I'm
        // using the iterator to get the key rather than than the object.
        delete m_store[itr->first];

    }

}



// loadCommodities()
// Takes a filename and inserts the commodities in the file into the map.
void CommodityStore::loadCommodities(string filename) {

    ifstream fileIn;
    fileIn.open(filename.c_str(), fileIn.in);


    while(!fileIn.eof()) {

        string commodityName;
        string commodityColor;

        fileIn >> commodityName;
        fileIn >> commodityColor;

        // Get rid of our issues with the final line.
        if(commodityName == "") {
            fileIn.close();
            return;
        }

//        cerr << commodityName << " " << commodityColor << endl;

        // Create the new commodity and add it to the map.
        Commodity* newComm = new Commodity(commodityName, commodityColor);
        m_store[commodityName] = newComm;
    }

    fileIn.close();

    // Special thanks: http://stackoverflow.com/a/237280/1021259
}



void CommodityStore::printCommodities(ofstream& fileStream) {

    fileStream << "---------- Commodities ----------" << endl;

    // Special thanks: http://stackoverflow.com/a/4844904/1021259 for this line:
    typedef map<string, Commodity*>::iterator it_type;

    for(it_type itr = m_store.begin(); itr != m_store.end(); itr++) {

        Commodity* on = m_store[itr->first];

        fileStream << on->getName() << " " << on->colorToString(on->getColor()) << endl;

    }

    fileStream << "--------------------------" << endl;
}

Commodity* CommodityStore::getCommodity(string name) {
//    cerr << name << endl;

    try {
        return m_store.at(name);
    } catch(exception e) {
        throw StoreException("No commodity with given name.");
    }
}

