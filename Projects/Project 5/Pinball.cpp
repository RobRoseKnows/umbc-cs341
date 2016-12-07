/*
 * File:    Pinball.cpp
 * Author:  Robert
 * Section: 3
 * Created: Dec 6, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "Pinball.h"
#include <string.h>

Pinball::Pinball(int n=1019) {

    H = (char**) malloc(n * sizeof(char*));
    memset(H, 0, n * sizeof(char*));

    m_size = 0;
    m_capacity = n;

    m_seeds = new int[n];

    for(int i = 0; i < n; i++) {
        m_seeds[i] = rand();
    }

    m_total_hits = 0;
    m_total_primary_slots = 0;
    m_total_ejections = 0;
    m_max_num_ejections = 0;
}



Pinball::~Pinball() {

}



void Pinball::insert(const char *str) {

}



int Pinball::find(const char *str) {

}



const char * Pinball::at(int index) {

}



char * Pinball::remove(const char *str) {

}



void Pinball::printStats() {

}
