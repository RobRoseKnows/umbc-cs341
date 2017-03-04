// File: driver2cpp
//
// CMSC 341 Spring 2017 Project 2
//
// Simple driver program to call the Sally Forth interpreter
// This version accepts user input for filename of Sally Forth
// source code.
//


#include <iostream>
#include <fstream>
using namespace std ;

#include "Sally.h"

int main( int argc, char *argv[] ) {
   
    if(argc < 2) {
        
        string fname ;

        cout << "Enter file name: " ;
        cin >> fname ;
        ifstream ifile(fname.c_str()) ;

        Sally S(ifile) ;

        S.mainLoop() ;

        ifile.close() ;

    } else {
        
        int on = 1;

        while(on < argc) {

            char* fname = argv[on];
            ifstream ifile(fname) ;
           
            cout << "Program: " << fname << endl;

            Sally S(ifile) ;
            S.mainLoop() ;
            ifile.close() ;
            on++;

        }

    }
    
    return 0 ;
}
