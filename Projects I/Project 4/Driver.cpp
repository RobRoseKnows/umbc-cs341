#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "PinHit.h"
#include "Heap.h"
#include "MinHeap.h"
#include "MaxHeap.h"

// Predefine the SearchResult class I'm going to use down bellow.
class SearchResult;

// global variable for type of heap
std::string heapType = "--max";


//forward declare so I can define it below main
void printGreeting();

std::vector<PinHit> ReadPins(char* fileName, int* totalHits);

template<class T, int m_size>
Heap<T, m_size>* BuildHeap(std::vector<T> PinHits, int slots);

// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, std::vector<T> PinHits, int totalHits);


// This allows us to add new pin appearances without needing to traverse through the entire
// list each time. It keeps the vector sorted and only inserts things in the order they're
// supposed to go.
//
// Takes: a list of PinHits and a PinHit to insert
// Returns: the new vector with the PinHit inserted.
void insertSortWise(std::vector<PinHit>& list, PinHit ph);


// This allows us to find the PinHit we're looking for in O(logn) time, without needing to
// traverse the entire list each time.
//
// Takes: a list of PinHits and the pin to search for
// Returns: the index of the requested PinHit instance or the next one below it. -1 if list is empty.
int binarySearchForPin(std::vector<PinHit>& list, int pin);


// I used a sorted list for this because it makes it easier to add duplicate pins.
// Although a non-sorted list could add new pins in O(1) time, it would need O(n)
// time to check to make sure it doesn't already exist in the list. By putting it
// in a sorted list and using Binary Search, we can insert things in log(n) time.


int main(int argc, char* argv[]) {

    std::string fileName;

    if(argc > 2) {
        heapType = argv[2];
    } else {
        return EXIT_FAILURE;
    }

	printGreeting();

	int totalPins = 0;
	std::vector<PinHit> list = ReadPins(argv[1], &totalPins);

	std::cerr << "List: ";
	for(int i = 0; i < list.size(); i++) {
	    std::cerr << list.at(i).GetKey() << " ";
	}
	std::cerr << std::endl;

	Heap<PinHit, 10000>* heap = BuildHeap<PinHit, 10000>(list, totalPins);

	int successes = Hack(heap, list, totalPins);
	std::cout << successes << std::endl;


	return EXIT_SUCCESS;
}

// prints your name and section
void printGreeting() {
	std::cout << "Robert Rose, Section 03" << std::endl;
}



// implement these two functions
std::vector<PinHit> ReadPins(char* fileName, int* totalHits) {

    std::ifstream in(fileName);

    std::vector<PinHit> list;

    int nextPin;

    while(in >> nextPin) {

        PinHit newPH(nextPin, 0);

        (*totalHits)++;

    }

    in.close();

    return list;

}



template<class T, int m_size>
Heap<T, m_size>* BuildHeap(std::vector<T> PinHits, int slots) {

    Heap<T, m_size>* heap;

    if (heapType == "--min") {

        heap = new MinHeap<T, m_size>();

    } else if (heapType == "--max") {

        heap = new MaxHeap<T, m_size>();

    } else {

        heap = new Heap<T, m_size>();

    }

    for(int i = 0; i < PinHits.size(); i++) {

        heap->Insert(PinHits[i]);

    }

    return heap;

}



void insertSortWise(std::vector<PinHit>& list, PinHit ph) {

    // Find either the index of the current pin in the list or the index of the one
    int index = binarySearchForPin(list, ph.GetKey());

    if(index < 0) {

        list.push_back(ph);
        return;

    }

    // Check to make sure we shouldn't be adding this to the end of the list.
    if(index + 1 < list.size()) {

        // Check to see if we found the PinHit or not.
        if(list[index].GetKey() == ph.GetKey()) {

            // If we actually found the PinHit, increment it.
            list[index].IncrementHits();
            return;

        } else {

            // If we're here it means that we didn't find the pin in the list and we're going to have to add it ourselves.

//            if(list[index].GetKey() > ph.GetKey()) {
//
//                // Sanity check to make sure the PinHit below us is actually a lower pin.
//                std::cerr << "Error: binary search returned a pin greater than our current." << std::endl;
//                return;
//
//            }

            // Because insert adds the element before, we have to add one to the index.
            list.insert(list.begin() + index + 1, ph);
            return;

        }

    } else {

        list.push_back(ph);
        return;

    }

}



// This is an implementation of Binary Search.
int binarySearchForPin(std::vector<PinHit>& list, int pin) {

    // Catch if the array is empty, saves time later on.
    if(list.size() < 1) {
        return -1;
    }

    int left = 0;
    int right = list.size() - 1;

    int mid;

    while(left <= right) {

       mid = left + (right - left) / 2;

       if(list[mid].GetKey() < pin) {

           left = mid + 1;

       } else if(list[mid].GetKey() > pin) {

           right = mid - 1;

       } else {

           // We found the pin!
           return mid;

       }

    }

    return mid;

}




// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, std::vector<T> PinHits, int totalHits) {

	int UPPER_BOUND = totalHits; // used for failsafes

	/*
	* His fictional bank with fictional cards and 
	* "normal pins" will allow you to incorrectly attempt 
	* to access his card 3 times per hour. You have from 
	* the start of the assignment to the end to hack as 
	* many accounts as possible (14 days * 24 hr/day * 3 
	* attempts/hr = 1008 attempts per card)
	*/
	int MAX_ATTEMPTS = 1008;

	int hackAttemptsLeft = MAX_ATTEMPTS;
	int successfulHacks = 0;


	srand (1337); // seeds our random generator with the current time
	int randomNumHits = rand() % totalHits; // generates a random hit between 0 and total hits	

	int curHits = 0; // our variable for crawling
	int randomIndex = -1; // the index where our new random pinhit lives
	int newHits = 0; // number of hits in new "random" pin
	int failSafe = 0; // always good to have one of these in what could be an infinite loop

	/* 
	* Linearly searches through PinHits until
	* we've accrued enough hits to reach our random hits
	* which will then determine the next pin to try to hack.
	* We use newHits to make sure we don't pick a random pin
	* that's not in our heap. 
	*/
	PinHit curPinHit;
	while (newHits == 0 && failSafe < UPPER_BOUND) {

		for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
			curHits += PinHits[i].GetValue();
			randomIndex = i;
		}
		// should have found the random pin by now
		curPinHit = PinHits[randomIndex];
		newHits = curPinHit.GetValue(); // make sure it's actually in our heap
		std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
		failSafe++;
	}

	// let's make a copy of the heap so we don't modify the original.
	Heap<T, m_size>* heapCopy;

	if (heapType == "--min") {
		heapCopy = new MinHeap<T, m_size>(*heap);
	} else if (heapType == "--max") {
		heapCopy = new MaxHeap<T, m_size>(*heap);
	} else {
		heapCopy = new Heap<T, m_size>(*heap);
	}

	failSafe = 0;

	PinHit defaultPin;

	// exit once hacking 10000 accounts, either a hacking prodigy or something is wrong
	int MAX_NUM_HACKS = 10000;

	while (0 < hackAttemptsLeft && successfulHacks < MAX_NUM_HACKS) {

		// grabs our root
		PinHit topOfHeap = heapCopy->Remove();
		if (topOfHeap == defaultPin)
			break;

		std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << " our last attempt" << std::endl;

		if (hackAttemptsLeft == 1)
		std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << " our last attempt" << std::endl;

		hackAttemptsLeft--;

		// account was hacked!
		if (topOfHeap == curPinHit) {
			std::cout << "We got them!" << std::endl;
			successfulHacks++;

			// reset our heap
			if (heapType == "--min") {
				heapCopy = new MinHeap<T, m_size>(*heap);
			} else if (heapType == "--max") {
				heapCopy = new MaxHeap<T, m_size>(*heap);
			} else {
				heapCopy = new Heap<T, m_size>(*heap);
			}

			// reset
			hackAttemptsLeft = MAX_ATTEMPTS;
			randomNumHits = rand() % totalHits;
			curHits = 0;
			randomIndex = -1;
			newHits = 0;
			failSafe = 0;
			while (newHits == 0 && failSafe < UPPER_BOUND) {

				for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
					curHits += PinHits[i].GetValue();
					randomIndex = i;
				}
				// should have found the random pin by now
				curPinHit = PinHits[randomIndex];
				newHits = curPinHit.GetValue(); // make sure it's actually in our heap
				std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
				failSafe++;
			}

			std::cout << "Valid Random Pin: " << curPinHit.GetKey() << " found!" << std::endl;
		}
	}	

	return successfulHacks;

}
