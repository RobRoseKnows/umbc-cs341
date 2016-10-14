#ifndef GAME_H_
#define GAME_H_
/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include<vector>
#include<stack>
#include<iostream>

using namespace std;

#include "Player.h"

class Player;
class Card;
class CommodityStore;

class Game {
public:
    void runSimulation(int players, Player::STRATEGY strategy);
    void printDrawPile(ofstream& fileStream);
    void printResults(ofstream& fileStream);
private:
    stack<Card*> m_drawPile;
    vector<Player*> m_players;
    CommodityStore m_bank;

};
#endif
