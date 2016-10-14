/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/11/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */
#include <iostream>

using namespace std;

void printGreeting();

int main(int argc, char ** argv) {
    string cardFileName = "";
    string commodFileName = "";
    string playerFileName = "";
    string strat = "";

    if(argc == 4) {
        cardFileName = argv[0];
        commodFileName = argv[1];
        playerFileName = argv[2];
        strat = argv[3];
    } else {
        std::cerr << "Not enough arguments." << endl;
        return 1;
    }


}

void printGreeting() {
    std::cerr << "Robert Rose 3";
}
