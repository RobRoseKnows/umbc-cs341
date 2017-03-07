// File: Sally.cpp
// Author:  Robert Rose
// Section: 4
// E-mail:  robrose2@umbc.edu
// 
// CMSC 341 Spring 2017 Project 2
//
// Implementation of member functions of Sally Forth interpreter
//

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std ;

#include "Sally.h"

// This allows me to quickly disable the debugging statements I insert when
// testing.
#define SHOW_DEBUG false

// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
   m_kind = kind ;
   m_value = val ;
   m_text = txt ;
}


// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
   m_kind = kind ;
   m_value = val ;
   m_dothis = fptr ;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
       istrm(input_stream)  // use member initializer to bind reference
{
    if(SHOW_DEBUG) cerr << "Showing Debug Messages..." << endl;

    m_isRecord = false;
    m_isSkip = false;
    m_isLoop = false;

    m_ifCount = 0;
    m_elseCount = 0;
    m_endIfCount = 0;

    // Debugging
    symtab["DUMP"]    =  SymTabEntry(KEYWORD,0,&doDUMP) ;

    // Arithmetic
    symtab["+"]     =   SymTabEntry(KEYWORD,0,&doPlus) ;
    symtab["-"]     =   SymTabEntry(KEYWORD,0,&doMinus) ;
    symtab["*"]     =   SymTabEntry(KEYWORD,0,&doTimes) ;
    symtab["/"]     =   SymTabEntry(KEYWORD,0,&doDivide) ;
    symtab["%"]     =   SymTabEntry(KEYWORD,0,&doMod) ;
    symtab["NEG"]   =   SymTabEntry(KEYWORD,0,&doNEG) ;

    // Printing
    symtab["."]     =   SymTabEntry(KEYWORD,0,&doDot) ;
    symtab["SP"]    =   SymTabEntry(KEYWORD,0,&doSP) ;
    symtab["CR"]    =   SymTabEntry(KEYWORD,0,&doCR) ;

    // Stacks
    symtab["DUP"]   =   SymTabEntry(KEYWORD,0,&doDUP) ;
    symtab["DROP"]  =   SymTabEntry(KEYWORD,0,&doDROP) ;
    symtab["SWAP"]  =   SymTabEntry(KEYWORD,0,&doSWAP) ;
    symtab["ROT"]   =   SymTabEntry(KEYWORD,0,&doROT) ;

    // Variables
    symtab["SET"]   =   SymTabEntry(KEYWORD,0,&doSET) ;
    symtab["@"]     =   SymTabEntry(KEYWORD,0,&doFetch) ;
    symtab["!"]     =   SymTabEntry(KEYWORD,0,&doStore) ;

    // Comparison
    symtab["<"]     =   SymTabEntry(KEYWORD,0,&doLessThan);
    symtab["<="]    =   SymTabEntry(KEYWORD,0,&doLessThanOrEquals);
    symtab["=="]    =   SymTabEntry(KEYWORD,0,&doEquals);
    symtab["!="]    =   SymTabEntry(KEYWORD,0,&doNotEquals);
    symtab[">="]    =   SymTabEntry(KEYWORD,0,&doGreaterThanOrEquals) ;
    symtab[">"]     =   SymTabEntry(KEYWORD,0,&doGreaterThan) ;

    symtab["AND"]   =   SymTabEntry(KEYWORD,0,&doAND) ;
    symtab["OR"]    =   SymTabEntry(KEYWORD,0,&doOR) ;
    symtab["NOT"]   =   SymTabEntry(KEYWORD,0,&doNOT) ;

    symtab["IFTHEN"]=   SymTabEntry(KEYWORD,0,&doIFTHEN) ;
    symtab["ELSE"]  =   SymTabEntry(KEYWORD,0,&doELSE) ;
    symtab["ENDIF"] =   SymTabEntry(KEYWORD,0,&doENDIF) ;

    symtab["DO"]    =   SymTabEntry(KEYWORD,0,&doDO) ;
    symtab["UNTIL"] =   SymTabEntry(KEYWORD,0,&doUNTIL) ;

}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
 
   string line ;     // single line of input
   int pos ;         // current position in the line
   int len ;         // # of char in current token
   long int n ;      // int value of token
   char *endPtr ;    // used with strtol()


   while(true) {    // keep reading until empty line read or eof

      // get one line from standard in
      //
      getline(istrm, line) ;   

      // if "normal" empty line encountered, return to mainLoop
      //
      if ( line.empty() && !istrm.eof() ) {
         return true ;
      }

      // if eof encountered, return to mainLoop, but say no more
      // input available
      //
      if ( istrm.eof() )  {
         return false ;
      }


      // Process line read

      pos = 0 ;                      // start from the beginning

      // skip over initial spaces & tabs
      //
      while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
         pos++ ; 
      }

      // Keep going until end of line
      //
      while (line[pos] != '\0') {

         // is it a comment?? skip rest of line.
         //
         if (line[pos] == '/' && line[pos+1] == '/') break ;

         // is it a string literal? 
         //
         if (line[pos] == '.' && line[pos+1] == '"') {

            pos += 2 ;  // skip over the ."
            len = 0 ;   // track length of literal

            // look for matching quote or end of line
            //
            while(line[pos+len] != '\0' && line[pos+len] != '"') {
               len++ ;
            }

            // make new string with characters from
            // line[pos] to line[pos+len-1]
            string literal(line,pos,len) ;  // copy from pos for len chars

            // Add to token list
            //
            tkBuffer.push_back( Token(STRING,0,literal) ) ;  

            // Different update if end reached or " found
            //
            if (line[pos+len] == '\0') {
               pos = pos + len ;
            } else {
               pos = pos + len + 1 ;
            }

         } else {  // otherwise "normal" token

            len = 0 ;  // track length of token

            // line[pos] should be an non-white space character
            // look for end of line or space or tab
            //
            while(line[pos+len] != '\0' && line[pos+len] != ' ' && line[pos+len] != '\t') {
               len++ ;
            }

            string literal(line,pos,len) ;   // copy form pos for len chars
            pos = pos + len ;

            // Try to convert to a number
            //
            n = strtol(literal.c_str(), &endPtr, 10) ;

            if (*endPtr == '\0') {
               tkBuffer.push_back( Token(INTEGER,n,literal) ) ;
            } else {
               tkBuffer.push_back( Token(UNKNOWN,0,literal) ) ;
            }
         }

         // skip over trailing spaces & tabs
         //
         while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
            pos++ ; 
         }

      }
   }

}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
    Token tk ;
    bool more = true ;

    do {
        //do {
        if(SHOW_DEBUG) cerr << "In nextToken loop" << endl;
        while(more && tkBuffer.empty() ) {
            more = fillBuffer() ;
        }

        if ( !more && tkBuffer.empty() && recordingLoop.empty() ) {
            throw EOProgram("End of Program") ;
        }

        if(m_isRecord) {

            if(SHOW_DEBUG) cerr << "is recording" << endl;
            tk = tkBuffer.front();
            recordingLoop.push_back(tk);
            tkBuffer.pop_front(); 

        } else if(m_isLoop) {

            if(SHOW_DEBUG) cerr << "Is looping" << endl;
            tk = recordingLoop.front();
            recordingLoop.pop_front();
            recordingLoop.push_back(tk);

        } else {
        
            if(SHOW_DEBUG) cerr << "is not looping" << endl;
            tk = tkBuffer.front() ;
            tkBuffer.pop_front() ;
        }

        if(SHOW_DEBUG) cerr << "Token in Next: " << tokenIdentifier(tk) << endl;

        //} while(m_isRecord);

        // While the program is supposed to be skipping and tk isn't a 
        // ifthen keyword, keep looking for more tokens.
    } while(!tokenIsIfKeyword(tk) && m_isSkip) ;



    return tk ;
}


// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {
    
    Token tk ;
    map<string,SymTabEntry>::iterator it ;
    
    m_ifCount       = 0;
    m_elseCount     = 0;
    m_endIfCount    = 0;

    try {
        
        while( 1 ) {
            
            tk = nextToken() ;  

            if(SHOW_DEBUG) cerr << "Token: " << tokenIdentifier(tk) << endl;

            if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

                // if INTEGER or STRING just push onto stack
                params.push(tk) ;

            } else {

                it = symtab.find(tk.m_text) ;

                if ( it == symtab.end() )  {   // not in symtab

                    params.push(tk) ;

                } else if(it->second.m_kind == KEYWORD) {  
                    // invoke the function for this operation
                    //
                    it->second.m_dothis(this) ;   
                    tk.m_kind = KEYWORD;

                } else if (it->second.m_kind == VARIABLE) {

                    // variables are pushed as tokens
                    //
                    tk.m_kind = VARIABLE ;
                    params.push(tk) ;

                } else {

                    // default action
                    //
                    params.push(tk) ;

                }

            } // End if(integer || string)
            
          //  cout << "Token: " << tk.m_text << " Kind: " << tokenKindAsString(tk.m_kind) << endl;
        } // end while

    } catch (EOProgram& e) {

        cerr << "End of Program\n" ;
        if ( params.size() == 0 ) {
            cerr << "Parameter stack empty.\n" ;
        } else {
            cerr << "Parameter stack has " << params.size() << " token(s).\n" ;
        }

    } catch (out_of_range& e) {
        cerr << "Parameter stack underflow??\n" ;
    }// catch (...) {
       // cerr << "Unexpected exception caught\n" ;
    //}
}



//////////////////////////////////////////////////////////
// Arithmetic Operators                                 //
//////////////////////////////////////////////////////////

void Sally::doPlus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value + p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMinus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for -.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value - p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doTimes(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for *.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value * p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doDivide(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for /.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value / p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMod(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for %.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value % p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doNEG(Sally *Sptr) {
   Token p ;

   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for NEG.") ;
   }
   p = Sptr->params.top() ;
   Sptr->params.pop() ;
   Sptr->params.push( Token(INTEGER, -p.m_value, "") ) ;
}



//////////////////////////////////////////////////////////
// Printing operations                                  //
//////////////////////////////////////////////////////////

void Sally::doDot(Sally *Sptr) {

   Token p ;
   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for .") ;
   }

   p = Sptr->params.top() ;
   Sptr->params.pop() ;

   if (p.m_kind == INTEGER) {
      cout << p.m_value ;
   } else {
      cout << p.m_text ;
   }
}


void Sally::doSP(Sally *Sptr) {
   cout << " " ;
}


void Sally::doCR(Sally *Sptr) {
   cout << endl ;
}



//////////////////////////////////////////////////////////
// Debugging Operator (DUMP)                            //
//////////////////////////////////////////////////////////


void Sally::doDUMP(Sally *Sptr) {
    // do whatever for debugging

    stack<Token> paramsCopy = Sptr->params;

    cout << endl;
    cout << "Stack Dumped. Size: " << paramsCopy.size() << "." << endl;
    cout << "If Count: "    << Sptr->m_ifCount 
        << " Else Count: "  << Sptr->m_elseCount 
        << " End Count: "   << Sptr->m_endIfCount << endl;
    cout << "Skip: "    << Sptr->m_isSkip
        << " Record: "  << Sptr->m_isRecord
        << " Loop: "    << Sptr->m_isLoop << endl;
    cout << "Num in Loop: " << Sptr->recordingLoop.size() << endl;

    while(!paramsCopy.empty()) {
       
        // Get the token at the top 
        Token nextTk = paramsCopy.top() ;
        
        if(nextTk.m_kind == INTEGER) {
            
            // If the token is an integer, we should just print it out
            cerr << nextTk.m_value << " ";
        
        } else if(nextTk.m_kind == VARIABLE) {
            
            // This code is to let us print out the value of a variable when
            // we print one out.
            SymTabEntry var = Sptr->symtab[nextTk.m_text];
            if(Sptr->symtab.find(nextTk.m_text) != Sptr->symtab.end()) {
                cerr << nextTk.m_text.c_str() << "=" << var.m_value << " ";
            } else {
                cerr << nextTk.m_text << "=NULL ";
            }

        } else if(nextTk.m_kind == KEYWORD) {
            
            // We should put a new line before each keyword so we can easily
            // tell appart different actions.
            cerr << endl << nextTk.m_text << " ";

        } else {
           
            // If the token is anything else, just print it out.
            cerr << nextTk.m_text << " ";
        
        }

        paramsCopy.pop();

    }

    cerr << endl;

} 



//////////////////////////////////////////////////////////
// Stack Operations                                     //
//////////////////////////////////////////////////////////


// The DUP operator takes the item at the top of the stack and duplicates
// it and adds it to the top of the stack.
//
// Usage: A DUP
// Stack: A A
//
void Sally::doDUP(Sally *Sptr) {

    if(Sptr->params.size() < 1) {
        throw out_of_range("Need at least one parameter for DUP");
    }

    Token p = Sptr->params.top() ;

    if(p.m_kind == INTEGER) {
        Sptr->params.push( Token(INTEGER, p.m_value, "") );
    } else {
        Sptr->params.push( Token(p.m_kind, 0, p.m_text) );
    }

}


// The DROP operator pops the first item on the stack, removing it.
//
// Usage: ... A DROP
// Stack: ...
void Sally::doDROP(Sally *Sptr) {

    if(Sptr->params.size() < 1) {
        throw out_of_range("Need at least one parameter for DROP") ;
    }

    Sptr->params.pop();

}


// This swaps the places of the first and second item on the parameter stack.
//
// Usage: A B SWAP
// Stack: B A
//
void Sally::doSWAP(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two parameters for SWAP");
    }

    // Remove the item at the top of the stack.
    Token pHigh = Sptr->params.top() ;
    Sptr->params.pop() ;

    // Remove the item that was below the previous one.
    Token pLow = Sptr->params.top() ;
    Sptr->params.pop() ;

    // Swap them.
    Sptr->params.push(pHigh) ;
    Sptr->params.push(pLow) ;

}


// This rotates the first three items at the top of the stack. It takes the
// 3rd item in the sack and puts it at the top, shifting the 1st and 2nd
// down by one.
//
// Usage: A B C ROT
// Stack: B C A
//
void Sally::doROT(Sally *Sptr) {

    if(Sptr->params.size() < 3) {
        throw out_of_range("Need at least three parameters for ROT.");
    }

    // Given: A B C ROT
    // Want: B C A
    
    // Grab C and pop it out
    Token pFromTop = Sptr->params.top();
    Sptr->params.pop();

    // Grab B and pop it out
    Token pFromMiddle = Sptr->params.top() ;
    Sptr->params.pop();

    // Grab A and pop it out
    Token pFromBottom = Sptr->params.top() ;
    Sptr->params.pop() ;

    // Add them back in so it's B C A
    Sptr->params.push(pFromMiddle) ;
    Sptr->params.push(pFromTop) ;
    Sptr->params.push(pFromBottom) ;

}



//////////////////////////////////////////////////////////
// Variable Operations                                  //
//////////////////////////////////////////////////////////


// SET initializes a variable with a given value. It creates new variables
// and cannot be used to set preexisting ones.
//
// Usage: <value> <variable> SET
//
void Sally::doSET(Sally *Sptr) {
    // TODO: It might be neccessary to come back and add checks as to whether
    // or not the variable token we're using is actually a variable.


    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for SET operator.") ;
    }

    // Get the first item on the stack, it will be the variable we're
    // supposed to create.
    Token pVariable = Sptr->params.top() ;
    Sptr->params.pop() ;

    // Get the second item on the stack, it will be the integer value we're
    // supposed to intiialize the variable with.
    Token pValue = Sptr->params.top();
    Sptr->params.pop() ;
    
    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pValue)) {
    
        // We need to check to make sure the variable isn't already in the
        // symbol table.
        if(Sptr->symtab.find(pVariable.m_text) == Sptr->symtab.end()) {
  
            SymTabEntry newEntry = SymTabEntry(VARIABLE, pValue.m_value);
            pair<string, SymTabEntry> newPair = 
                pair<string, SymTabEntry>(pVariable.m_text, newEntry) ;
            Sptr->symtab.insert(newPair) ;        
  
        } else {
            cerr << "SYNTAX ERROR: The variable `" << pVariable.m_text 
                << "` already exists in the symbol table." << endl;
        }
    
    }
}


// The fetch or `@` operator looks a variable up in the symbol table and
// adds its value to the top of the stack.
//
// Usage: <variable> @
// Stack: <variable.m_value>
//
void Sally::doFetch(Sally *Sptr) {

    if(Sptr->params.size() < 1) {
        throw out_of_range("Need at least one token for the fetch ");
    }
    
    Token pVariable = Sptr->params.top() ;
    Sptr->params.pop();    
    
    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmVariable(pVariable)) {

        if(Sptr->symtab.find(pVariable.m_text) != Sptr->symtab.end()) {
  
            SymTabEntry entry = Sptr->symtab[pVariable.m_text];
            Sptr->params.push(Token(INTEGER, entry.m_value));
  
        } else {
            cerr << "SYNTAX ERROR: The variable `" << pVariable.m_text 
                << "` does not exist in the symbol table." << endl;
        }
    }
}


// The store or `!` operator stores a value on the stack as a variable in
// the symbol table.
//
// Usage: <value> <variable> !
// 
void Sally::doStore(Sally *Sptr) {
    
    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for store operation.");
    }    

    
    // Get the first item on the stack, it will be the variable we're
    // supposed to set.
    Token pVariable = Sptr->params.top() ;
    Sptr->params.pop() ;

    // Get the second item on the stack, it will be the integer value we're
    // supposed to set the variable to.
    Token pValue = Sptr->params.top();
    Sptr->params.pop() ;


    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pValue) & confirmVariable(pVariable)) {
        // We need to check to make sure the variable is in the symbol table
        if(Sptr->symtab.find(pVariable.m_text) != Sptr->symtab.end()) {
  
            SymTabEntry* entry = &Sptr->symtab[pVariable.m_text];
            entry->m_value = pValue.m_value;
  
        } else {
            cerr << "SYNTAX ERROR: The variable `" << pVariable.m_text 
                << "` does not exist in the symbol table." << endl;
        }

    }
}




//////////////////////////////////////////////////////////
// Variable Operations                                  //
//////////////////////////////////////////////////////////

// LHS < RHS
void Sally::doLessThan(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for < operation.");
    }    

    Token pRHS = Sptr->params.top();
    Sptr->params.pop();

    Token pLHS = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pRHS) & confirmInteger(pLHS)) {
        // Compare them with subtraction.
        int comp = pLHS.m_value - pRHS.m_value;

        // If LHS - RHS is greater than or equal to 0, it means the LHS is
        // greater than the RHS and therefore the statement is false, so we 
        // set it to 0.
        if(comp >= 0) {
            comp = boolToNum(false);
        } else {
            comp = boolToNum(true);
        }

        Token answer = Token(INTEGER, comp) ;
        Sptr->params.push(answer) ;
    }
}


void Sally::doLessThanOrEquals(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for <= operation.");
    }    

    Token pRHS = Sptr->params.top();
    Sptr->params.pop();

    Token pLHS = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pRHS) & confirmInteger(pLHS)) {
        
        // Compare them via subtraction.
        int comp = pLHS.m_value - pRHS.m_value;

        // If LHS - RHS is greater than 0, it means the LHS is greater than 
        // the RHS and therefore the statement is false, so we set it to 0.
        if(comp > 0) {
            comp = boolToNum(false);
        } else {
            comp = boolToNum(true);
        }

        Token answer = Token(INTEGER, comp) ;
        Sptr->params.push(answer) ;

    }
}



void Sally::doEquals(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for == operation.");
    }    

    Token pRHS = Sptr->params.top();
    Sptr->params.pop();

    Token pLHS = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pRHS) & confirmInteger(pLHS)) {
    
        // Compare via subtraction.
        int comp = pLHS.m_value - pRHS.m_value;

        // If LHS - RHS is not equal to 0, set it to zero because that means
        // they are not equal to each other. 
        if(comp != 0) {
            comp = boolToNum(false);
        } else {
            // If it is equal, we set it to 1. This is kind of backwards as we
            // switch what is 0 to something else and something else to 0.
            comp = boolToNum(true);
        }

        Token answer = Token(INTEGER, comp) ;
        Sptr->params.push(answer) ;

    }
}



void Sally::doNotEquals(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for != operation.");
    }    

    Token pRHS = Sptr->params.top();
    Sptr->params.pop();

    Token pLHS = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pRHS) & confirmInteger(pLHS)) {
        // Compare via subtraction.
        int comp = pLHS.m_value - pRHS.m_value;

        // If LHS - RHS is equal to 0, set it to zero because that means 
        // they are equal to each other. Technically we don't actually need 
        // to set it to 0 but I decided to do so any way for consistencies 
        // sake.
        if(comp == 0) {
            comp = boolToNum(false);
        } else {
            // If it isn't equal to 0, we set it to 1 because that means they
            // are not equal to each other.
            comp = boolToNum(true);
        }      

        Token answer = Token(INTEGER, comp) ;
        Sptr->params.push(answer) ;
    }
}



void Sally::doGreaterThanOrEquals(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for >= operation.");
    }    

    Token pRHS = Sptr->params.top();
    Sptr->params.pop();

    Token pLHS = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pRHS) & confirmInteger(pLHS)) {
        // Compare them via subtraction.
        int comp = pLHS.m_value - pRHS.m_value;

        // If LHS - RHS is less than 0, it means the LHS is less than the 
        // RHS.
        if(comp < 0) {
            // My reasoning behind using these boolToNum functions is to make
            // it more clear what each value means.
            comp = boolToNum(false);
        } else {
            comp = boolToNum(true);
        }

        Token answer = Token(INTEGER, comp) ;
        Sptr->params.push(answer) ;

    }
}



void Sally::doGreaterThan(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for > operation.");
    }    

    Token pRHS = Sptr->params.top();
    Sptr->params.pop();

    Token pLHS = Sptr->params.top();
    Sptr->params.pop();
    
    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmInteger(pRHS) & confirmInteger(pLHS)) {
        // Compare them via subtraction.
        int comp = pLHS.m_value - pRHS.m_value;

        // If LHS - RHS is less than or equal to 0, it means the LHS is less 
        // than or equal to the RHS.
        if(comp <= 0) {
            comp = boolToNum(false);
        } else {
            comp = boolToNum(true);
        }

        Token answer = Token(INTEGER, comp) ;
        Sptr->params.push(answer) ;
    }
}



//////////////////////////////////////////////////////////
// Logic Operators                                      //
//////////////////////////////////////////////////////////

void Sally::doAND(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for AND operation.");
    }    

    Token p1 = Sptr->params.top();
    Sptr->params.pop();

    Token p2 = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmBoolean(p1) & confirmBoolean(p2)) {
        
        // Convert the numbers into boolean values so we can use boolean
        // operations on them.
        bool p1AsBool = numToBool(p1.m_value);
        bool p2AsBool = numToBool(p2.m_value);

        // Now do the operation and save it as a bool.
        bool answer = p1AsBool && p2AsBool; 

        Sptr->params.push(Token(INTEGER, boolToNum(answer)));    
    }
}


void Sally::doOR(Sally *Sptr) {

    if(Sptr->params.size() < 2) {
        throw out_of_range("Need at least two tokens for OR operation.");
    }    

    Token p1 = Sptr->params.top();
    Sptr->params.pop();

    Token p2 = Sptr->params.top();
    Sptr->params.pop();

    // This single appersand is important so that both expressions are
    // evaluated and therefore both errors will appear if need be. 
    if(confirmBoolean(p1) & confirmBoolean(p2)) {
        bool p1AsBool = numToBool(p1.m_value);
        bool p2AsBool = numToBool(p2.m_value);

        bool answer = p1AsBool || p2AsBool;
        Sptr->params.push(Token(INTEGER, boolToNum(answer)));
    }
}

void Sally::doNOT(Sally *Sptr) {

    if(Sptr->params.size() < 1) {
        throw out_of_range("Need at least one token for NOT operation.");
    }    

    Token p1 = Sptr->params.top();
    Sptr->params.pop();

    if(confirmBoolean(p1)) { 
        
        bool p1AsBool = numToBool(p1.m_value);

        bool answer = !p1AsBool;
        Sptr->params.push(Token(INTEGER, boolToNum(answer)));
    
    }
}



//////////////////////////////////////////////////////////
// IFTHEN ELSE Operators                                //
//////////////////////////////////////////////////////////

void Sally::doIFTHEN(Sally *Sptr) {
    
    Sptr->m_ifCount++;
   
    if(SHOW_DEBUG) cerr << "Top in IF: " << tokenBooleanValue(Sptr->params.top()) << endl;

    if(SHOW_DEBUG) cerr << "IF: " << Sptr->m_ifCount 
        << " ELSE: " << Sptr->m_elseCount 
            << " END: " << Sptr->m_endIfCount << endl;
    
    if(!Sptr->m_isSkip) {
        Sptr->m_isSkip = !tokenBooleanValue(Sptr->params.top());
    }

    Sptr->params.pop();

}


void Sally::doELSE(Sally *Sptr) {

    Sptr->m_elseCount++;

    if(SHOW_DEBUG) cerr << "IF: " << Sptr->m_ifCount 
        << " ELSE: " << Sptr->m_elseCount 
            << " END: " << Sptr->m_endIfCount << endl;
    
    if(Sptr->m_isSkip && Sptr->m_elseCount == Sptr->m_ifCount) {
        Sptr->m_isSkip = false;
    }
}


void Sally::doENDIF(Sally *Sptr) {
    Sptr->m_endIfCount++;

    if(SHOW_DEBUG) cerr << "IF: " << Sptr->m_ifCount 
        << " ELSE: " << Sptr->m_elseCount 
            << " END: " << Sptr->m_endIfCount << endl;

    if(Sptr->m_endIfCount == Sptr->m_ifCount) {
        Sptr->m_isSkip = false;
    }

}


//////////////////////////////////////////////////////////
// DO UNTIL Operators                                   //
//////////////////////////////////////////////////////////

void Sally::doDO(Sally *Sptr) {
   
    if(!Sptr->m_isRecord) {
        Sptr->m_isRecord = true;
    }
}
    
void Sally::doUNTIL(Sally *Sptr) {
   
    if(SHOW_DEBUG) cerr << "Entered UNTIL" << endl;

    Sptr->m_isRecord = false;
    Sptr->m_isLoop = !numToBool(Sptr->params.top().m_value);

    if(!Sptr->m_isLoop) {
        Sptr->recordingLoop.clear();
    }

    Sptr->params.pop();

}



//////////////////////////////////////////////////////////
// Helper Functions                                     //
//////////////////////////////////////////////////////////


// This converts a number into a boolean for us. We are using the definition
// that 0 is false and everything else is true. I'm going to set true equal
// to 1 in all defined usages however.
//
bool Sally::numToBool(int num) {
    
    if(num == 0) {
        return false;
    } else {
        return true;
    }

}



// This converts boolean values into numbers to store in the stack. Most of
// the time I use this to avoid having magic numbers.
//
int Sally::boolToNum(bool val) {
    if(val) {
        return 1;
    } else {
        return 0;
    }
}


bool Sally::tokenBooleanValue(const Token &tk) {
   
    if(confirmNotNull(tk)) { 
        if(confirmBoolean(tk)) {
            return tk.m_value;
        } else {
            return false;
        }
    }
}


// This method returns true if the given token is an integer and false
// otherwise. If it is not an integer, it prints out an error message.
// The error message printing is the main purpose of this helper function.
// 
bool Sally::confirmInteger(const Token &tk) {
    if(confirmNotNull(tk)) {
        if(tk.m_kind == INTEGER) {
            return true;
        } else {
            cerr << "Incorrect token type. Token `" << tokenIdentifier(tk) 
                << "` is a(n) `" << tokenKindAsString(tk.m_kind) 
                << ", not an INTEGER." << endl;
        }
    }
}
    


// This is the same thing as confirmInteger (because we store bool's as
// integers) but it has different error messages.
//
bool Sally::confirmBoolean(const Token &tk){

    if(confirmNotNull(tk)) {
        if(tk.m_kind == INTEGER) {
            return true;
        } else {
            cerr << "Incorrect token type. Token `" << tokenIdentifier(tk) 
                << "` is a(n) `" << tokenKindAsString(tk.m_kind) 
                << ", not an BOOLEAN aka INTEGER." << endl;
        }
    }
}


bool Sally::confirmNotNull(const Token &tk) {

    if(&tk != NULL) {
        return true;
    } else {
        cerr << "Invalid token. Token is NULL." << endl;
    }

}

// This method returns true if the given token is a variable and false
// otherwise. If it is not a variable, it prints out an error message.
// The error message printing is the main purpose of this helper function.
// 
bool Sally::confirmVariable(const Token &tk) {
    
    if(confirmNotNull(tk)){
        if(tk.m_kind == VARIABLE) {
            return true;
        } else {
            cerr << "Incorrect token type. Token `" << tokenIdentifier(tk) 
                << "` is a(n) `" << tokenKindAsString(tk.m_kind) 
                << ", not a VARIABLE." << endl;
        }

    }
}

// This prints out the kind of a token as a string instead of an enum so we
// can print it out elsewhere.
string Sally::tokenKindAsString(TokenKind kind) {
    switch(kind) {
        case UNKNOWN:
            return "UNKNOWN";
        case KEYWORD:
            return "KEYWORD";
        case INTEGER:
            return "INTEGER";
        case VARIABLE:
            return "VARIABLE";
        case STRING:
            return "STRING";
        default:
            return "INVALID KIND";
    }
}

// This returns a string that is either the `m_value` or `m_text` member
// of a token depending on what kind of token it is. If it is an Integer
// it uses the m_value property and it uses the m_text value otherwise.
// This makes it easier to print the messages for the confirm helper
// functions found above.
//
string Sally::tokenIdentifier(const Token &tk) {
   
    if(confirmNotNull(tk)) { 
        if(tk.m_kind == INTEGER) {
            ostringstream ss;
            ss << tk.m_value;
            return ss.str();
        } else {
            return tk.m_text;
        }
    }
}


bool Sally::tokenIsIfKeyword(const Token &tk) {
  
    return (tk.m_text == "IFTHEN") || (tk.m_text == "ELSE") || (tk.m_text == "ENDIF");

}
