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

#include<map>

using namespace std;

class Commodity;

class CommodityStore {
public:
    void loadCommodities(string filename);
    Commodity* getCommodity(string name);
private:
    map<string, Commodity*> m_store;
};
#endif
