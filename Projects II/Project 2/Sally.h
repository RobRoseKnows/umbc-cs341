//
// File:    Sally.h
// Author:  Robert Rose
// Section: 4
// E-mail:  robrose2@umbc.edu
//
// CMSC 341 Spring 2017 Project 2
//
// Class declarations for Sally Forth interpreter
//

#ifndef _SALLY_H_
#define _SALLY_H_

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <map>
#include <stdexcept>
using namespace std ;


// thrown by lexical parser when end of file reached
//
class EOProgram : public runtime_error {
public:
    EOProgram(const string& what) : runtime_error(what) { }
} ;


enum TokenKind { UNKNOWN, KEYWORD, INTEGER, VARIABLE, STRING } ;


// lexical parser returns a token 
// programs are lists of tokens
//
class Token {

public:

    Token(TokenKind kind=UNKNOWN, int val=0, string txt="" ) ;
    TokenKind m_kind ;
    int m_value ;      // if it's a known numeric value
    string m_text ;    // original text that created this token

} ;



// type of a C++ function that does the work 
// of a Sally Forth operation.
//
class Sally ; 
typedef void (* operation_t)(Sally *Sptr) ;



// entry in the symbol table has this type
//
class SymTabEntry {
public:
    SymTabEntry(TokenKind kind=UNKNOWN, int val=0, operation_t fptr=NULL) ;
    TokenKind m_kind ;
    int m_value ;            // variables' values are stored here
    operation_t m_dothis ;   // pointer to a function that does the work
} ;



// Main Sally Forth class
//
class Sally {

public:

    Sally(istream& input_stream=cin) ;  // make a Sally Forth interpreter

    void mainLoop() ;  // do the main interpreter loop


private:

    // Where to read the input
    //
    istream& istrm ;


    // Sally Forth operations to be interpreted
    //
    list<Token> tkBuffer ;   


    // Sally Forth parameter stack
    //
    stack<Token> params ;    


    // Sally Forth symbol table
    // keywords and variables are store here
    //
    map<string,SymTabEntry> symtab ;   


    // add tokens from input to tkBuffer
    //
    bool fillBuffer() ;


    // give me one more token.
    // calls fillBuffer() for you if needed.
    //
    Token nextToken() ;

//////////////////////////////////////////////////////////
// Operators                                            //
//////////////////////////////////////////////////////////

    // static member functions that do what has
    // to be done for each Sally Forth operation
    // 
    // pointers to these functions are stored 
    // in the symbol table
    //
    static void doDUMP(Sally *Sptr) ;    // for debugging

    // Arithmetic operators.
    //

    static void doPlus(Sally *Sptr) ;
    static void doMinus(Sally *Sptr) ;
    static void doTimes(Sally *Sptr) ;
    static void doDivide(Sally *Sptr) ;
    static void doMod(Sally *Sptr) ;
    static void doNEG(Sally *Sptr) ;

    // Printing operators
    // 

    static void doDot(Sally *Sptr) ;
    static void doSP(Sally *Sptr) ;
    static void doCR(Sally *Sptr) ;

    // Stack operators
    //

    static void doDUP(Sally *Sptr) ;
    static void doDROP(Sally *Sptr) ;
    static void doSWAP(Sally *Sptr) ;
    static void doROT(Sally *Sptr) ;

    // Variable operators
    //

    static void doSET(Sally *Sptr) ;
    static void doFetch(Sally *Sptr) ;
    static void doStore(Sally *Sptr) ;

    // Comparison operators
    //

    static void doLessThan(Sally *Sptr) ;
    static void doLessThanOrEquals(Sally *Sptr) ;
    static void doEquals(Sally *Sptr) ;
    static void doNotEquals(Sally *Sptr) ;
    static void doGreaterThanOrEquals(Sally *Sptr) ;
    static void doGreaterThan(Sally *Sptr) ;

    // Logic operations
    //

    static void doAND(Sally *Sptr);
    static void doOR(Sally *Sptr);
    static void doNOT(Sally *Sptr);
    
    // If Statements
    //

    static void doIFTHEN(Sally *Sptr);
    static void doELSE(Sally *Sptr);
    static void doENDIF(Sally *Sptr);

    // Do Until Operations
    //

    static void doDO(Sally *Sptr);
    static void doUNTIL(Sally *Sptr);


//////////////////////////////////////////////////////////
// Member variables for IFTHEN Statements               //
//////////////////////////////////////////////////////////

    int m_ifCount;
    int m_elseCount;
    int m_endIfCount;

    bool m_isSkip;

    stack<bool> hasExecuted;

/////////////////////////////////////////////////////////
// Member variables for DO UNTIL Statements            //
/////////////////////////////////////////////////////////

    bool m_isRecord;
    bool m_isLoop;
    list<Token> recordingLoop;

//////////////////////////////////////////////////////////
// Helper Functions                                     //
//////////////////////////////////////////////////////////

    static bool numToBool(int num);
    static int boolToNum(bool val);

    // This method takes a token and confirms whether or not it is a boolean
    // value. If it is, it returns the boolean value of that token. If it
    // isn't, it returns false and prints a message.
    //
    static bool tokenBooleanValue(const Token &tk);

    // This method returns true if the given token is an integer and false
    // otherwise. If it is not an integer, it prints out an error message.
    // The error message printing is the main purpose of this helper function.
    // 
    static bool confirmInteger(const Token &tk);
   
    // This is the same thing as confirmInteger (because we store bool's as
    // integers) but it has different error messages.
    //
    static bool confirmBoolean(const Token &tk);

    // This method returns true if the given token is a variable and false
    // otherwise. If it is not a variable, it prints out an error message.
    // The error message printing is the main purpose of this helper function.
    // 
    static bool confirmVariable(const Token &tk);

    // This returns a string representation of the kind of token provided.
    //
    static string tokenKindAsString(TokenKind kind);

    // This returns a string that is either the `m_value` or `m_text` member
    // of a token depending on what kind of token it is. If it is an Integer
    // it uses the m_value property and it uses the m_text value otherwise.
    // This makes it easier to print the messages for the confirm helper
    // functions found above.
    //
    static string tokenIdentifier(const Token &tk);

    static bool tokenIsIfKeyword(const Token &tk);

    static bool confirmNotNull(const Token &tk);

    static bool checkEmptyOrTrue(Sally *Sptr);
} ;

#endif
