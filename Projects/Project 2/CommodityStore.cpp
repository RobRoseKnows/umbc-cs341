/*
 * File:    CommodityStore.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "CommodityStore.h"

using namespace std;

CommodityStore::CommodityStore() {
    m_store = new map<string, Commodity*>;
}

void CommodityStore::loadCommodities(string filename) {

}

Commodity* CommodityStore::getCommodity(string name) {
    return m_store.find(name);
}

