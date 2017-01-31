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

#include <queue>
#include <fstream>
#include <string>

using namespace std;

class Objective;
class Card;

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

    Player(string name);
    ~Player();

    void addCard(Card* card);


    int getScore() const;


    int calculateScore(Player::STRATEGY strategy);


    void printResult(ofstream & fileStream);


    string strategyToString(STRATEGY strat);

    string getName() const {
        return m_sName;
    }


private:
    string m_sName;
    queue<Card*> m_cards;
    queue<Objective*> m_objectives;
};
#endif
