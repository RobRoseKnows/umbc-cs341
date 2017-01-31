#ifndef CS_H_
#define CS_H_
/*
 * File:    CommodityStore.h
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "Commodity.h"

#include<map>
#include<string>
#include<stdexcept>

using namespace std;

// This is thrown if there are any exceptions while running in the CommodityStore class.
class StoreException : public std::runtime_error {

   public:

    StoreException(const string& what) : std::runtime_error(what) { }

} ;

class CommodityStore {
public:


    ~CommodityStore();

    /****
     * Name: loadCommodities()
     * PreCondition:    Requires a list of commodities with name and color on the same line delimited
     *                  by a space. Each one should only be one word long. Different commodities
     *                  should be on different lines.
     * PostCondition:   All the commodities in the given file should now be in the map m_store.
     **/
    void loadCommodities(string filename);

    // This is for testing only.
    void printCommodities(ofstream& fileStream);

    Commodity* getCommodity(string name) ;
private:
    map<string, Commodity*> m_store;
};
#endif
