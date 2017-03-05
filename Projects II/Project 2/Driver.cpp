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

        // This is for if the user dosn't use the cool command line
        // arguments. It'll prompt for a file name.        
        string fname ;

        cout << "Enter file name: " ;
        cin >> fname ;
        ifstream ifile(fname.c_str()) ;

        Sally S(ifile) ;

        S.mainLoop() ;

        ifile.close() ;

    } else {
        
        // This chunk of code allows a user to specify a series of files
        // they would like to run by adding a series of files after the
        // command. 
        // 
        // This can work when using `make run` if you append FILES="A B C"...
        // to the end of your command. (Where A, B & C are Sally programs)
        int on = 1;

        while(on < argc) {

            char* fname = argv[on];
            ifstream ifile(fname) ;
          
            
            // Tell the user that we're running a different program now. 
            cout << "=== Program: " << fname << " ===" << endl;

            Sally S(ifile) ;
            S.mainLoop() ;
            ifile.close() ;
            on++;

            cout << endl;

        }

    }
    
    return 0 ;
}
