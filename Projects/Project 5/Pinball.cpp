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
#include <iostream>

Pinball::Pinball(int n) {

    H = (char**) malloc(n * sizeof(char*));
    memset(H, 0, n * sizeof(char*));

    m_size = 0;
    m_capacity = n;

    m_degree = DEGREE;
    m_ejectLimit = EJECTION_LIMIT;

    m_seeds = new int[n];
    for(int i = 0; i < n; i++) {
        m_seeds[i] = rand();
    }


    m_primaryHits = new int[n];
    for(int i = 0; i < n; i++) {
        m_primaryHits[i] = 0;
    }


    m_totalPrimarySlots = 0;

    m_totalEjections = 0;
    m_maxNumEjections = 0;

}



Pinball::~Pinball() {
    for(int i = 0; i < m_capacity; i++) {
        free(H[i]);
    }

    delete [] m_seeds;

    delete [] m_primaryHits;
}



void Pinball::insert(const char *str) {

    char* stringToInsert = strdup(str);
    unsigned int hashOfString = hashCode(stringToInsert);
    int indexOfString = hashOfString % m_capacity;

    // Increment the value of the primary slot.
    incrementPrimarySlot(indexOfString);

    int ejections = 0;
    bool done = false;

    while(ejections <= m_ejectLimit && !done) {


        if(H[indexOfString] == NULL) {

            // The primary slot is empty!
            H[indexOfString] = stringToInsert;
            done = true;
            break;
        } else {

//            cout << "Entered pinball insert else for " << stringToInsert << endl;

            // Create an array
            int* aux = createAuxArray(indexOfString);

            // This keeps track of whether or not we have found an empty spot.
            bool foundEmptySpotInAux = false;

            for(int i = 0; (i < m_degree - 1 && !foundEmptySpotInAux); i++) {

                if(H[aux[i]] == NULL) {

                    foundEmptySpotInAux = true;
                    H[aux[i]] = stringToInsert;
                    done = true;

                }

            }


            if(!foundEmptySpotInAux && !done) {
                int auxIndex = rand() % (m_degree - 1);

                // Insert and eject
                char* tempString = H[auxIndex];
                H[auxIndex] = stringToInsert;
                stringToInsert = tempString;

                // Get the new hash and index.
                hashOfString = hashCode(stringToInsert);
                indexOfString = hashOfString % m_capacity;

                // Increment the number of ejections.
                ejections++;
            }

            delete [] aux;

        }

    }

    m_totalEjections += ejections;

    if(ejections > m_maxNumEjections) {
        m_maxNumEjections = ejections;
    }

//    free(stringToInsert);

    if(ejections > m_ejectLimit) {
        throw PinballHashFull("Maximum ejections reached!");
    }

}



// This creates an array of aux indexes for functions to check.
int* Pinball::createAuxArray(int index) {

    int savedSeed = rand();
    int* aux = new int[m_degree - 1];

    // Set seed to option #1 pseduo-random seed
    srand(m_seeds[index]);

    // Modular degree
    for(int i = 0; i < m_degree - 1; i++) {
        aux[i] = rand() % m_capacity;
    }

    srand(savedSeed);

    return aux;

}



void Pinball::decrementPrimarySlot(int index) {

    // If nothing has been hashed to this slot before, it means there's a new
    // primary slot.
    if(m_primaryHits[index] == 1) {
        m_totalPrimarySlots--;
    }

    // Increment hits.
    m_primaryHits[index] -= 1;

}



void Pinball::incrementPrimarySlot(int index) {

    // If nothing has been hashed to this slot before, it means there's a new
    // primary slot.
    if(m_primaryHits[index] == 0) {
        m_totalPrimarySlots++;
    }

    // Increment hits.
    m_primaryHits[index] += 1;

}



int Pinball::find(const char *str) {

    if(strcmp(str, "reaffirmed") == 0) {
         cout << "reaffirmed NULL" << endl;
     }

    int index = -1;

    unsigned int hashOfString = hashCode(str);
    int indexOfString = hashOfString % m_capacity;

//    cout << "Hash: " << hashOfString << " index: " << indexOfString << endl;

    if(H[indexOfString] != NULL && strcmp(H[indexOfString], str) == 0) {

        index = indexOfString;

    } else {

        // Create an array
        int* aux = createAuxArray(indexOfString);

        // This keeps track of whether or not we have found an empty spot.
        bool foundInAux = false;

        for(int i = 0; i < m_degree - 1 && !foundInAux; i++) {

            if(H[aux[i]] != NULL && strcmp(H[aux[i]], str)) {

                index = aux[i];
                foundInAux = true;

            }

        }

        delete [] aux;
    }

    // If nothing, it'll return -1.
    return index;

}



const char * Pinball::at(int index) {
    return H[index];
}



char * Pinball::remove(const char *str) {

    char * toReturn = NULL;

    unsigned int hashOfString = hashCode(str);
    int indexOfString = hashOfString % m_capacity;

    if(strcmp(H[indexOfString], str) == 0) {

        toReturn = strdup(H[indexOfString]);
        decrementPrimarySlot(indexOfString);
        free(H[indexOfString]);

    } else {
        int* aux = createAuxArray(indexOfString);

        for(int i = 0; i < m_degree - 1; i++) {

            if(strcmp(H[aux[i]], str) == 0) {

               toReturn = strdup(H[aux[i]]);
               free(H[aux[i]]);

           }

        }
    }

    m_size--;

    return toReturn;

}



void Pinball::printStats(ostream& out) {

    out << "Hash statistics report:" << endl;
    out << "\trandomness level = pseudo-random" << endl;
    out << "\tcapacity = " << m_capacity << endl;
    out << "\tsize = " << m_size << endl;
    out << "\tdegree = " << m_degree << endl;
    out << "\tejection limit = " << m_ejectLimit << endl;
    out << "\tnumber of primary slots = " << m_totalPrimarySlots << endl;
    out << "\taverage hits to primary slots = " << getPrimaryAvg() << endl;
    out << "\tmaximum hits to primary slots = " << getPrimaryMax() << endl;
    out << "\ttotal number of ejections = " << m_totalEjections << endl;
    out << "\tmaximum number of ejections in a single insertion = " << m_maxNumEjections << endl;

}


double Pinball::getPrimaryAvg() {

    return (1.0 * m_size) / (1.0 * m_totalPrimarySlots);

}


int Pinball::getPrimaryMax() {

    int maxPrimary = 0;
    for(int i = 0; i < m_capacity; i++) {
        if(m_primaryHits[i] > maxPrimary) {
            maxPrimary = m_primaryHits[i];
        }
    }

    return maxPrimary;

}
