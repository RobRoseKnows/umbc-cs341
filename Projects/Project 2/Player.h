#ifndef PLAYER_H_
#define PLAYER_H_
/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include <stdlib.h>
#include <queue>

using namespace std;

class Card;
class Objective;

class Player {
public:
    enum STRATEGY {
        BEST_PAYOFF,
        FIRST_DESTINATION,
        COLOR_PURPLE,
        COLOR_RED,
        COLOR_ORANGE,
        COLOR_BLACK,
        COLOR_GREEN,
        COLOR_BROWN
    };

    string getName() const;
    int getScore() const;
    void addCard(Card* card);
    int calculateScore(Player::STRATEGY strategy);
    void printResult

private:
    string m_sName;
    queue<Card*> m_cards;
    queue<Objective*> m_objectives;
};
#endif
