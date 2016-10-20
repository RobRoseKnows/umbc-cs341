/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include "Player.h"

using namespace std;



Player::Player() {

}



Player::~Player() {

}



void Player::addCard(Card* card) {
    m_cards.push(card);
}



int Player::getScore() const {
    return 0;
}



int Player::calculateScore(Player::STRATEGY strategy) {
    return 0;
}



void Player::printResult(ofstream & fileStream) {

}
