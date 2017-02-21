/*
 * File:    Driver.cpp
 * Author:  Robert Rose
 * Date:    2/17/17
 * E-mail:  robrose2@umbc.edu
 */

#include "Graph.h"
#include <iostream>
#include <stdio.h> // Allows me to use printf

using namespace std;

void printNeighbors(Graph &G, int on); 
void printEdges(Graph &G); 

//////////////////////////////////////////////////////////////////////////
//                           START OF MAIN                              //
//////////////////////////////////////////////////////////////////////////
int main() {

    
    ///////////////////////////////////////////////////
    // Testing Functionality for Static Objects ///////
    ///////////////////////////////////////////////////
    cerr << "********************************" << endl;
    cerr << "********* Static Class *********" << endl;
    cerr << "********************************" << endl;

    cerr << "--------------------------------" << endl;
    cerr << "------ Test Constructor --------" << endl;
    cerr << "--------------------------------" << endl;
   
    cerr << "> Proper construction." << endl;

    Graph G = Graph(5) ;
    G.dump();
    cerr << endl;
    
    cerr << "> Negative size constructor:" << endl;
    try {
        cerr << "Trying -1 size for Gneg" << endl;
        Graph Gneg = Graph(-1);
    } catch(std::exception& err) {
        cerr << err.what() << endl;
    }
    cerr << endl;
    
    cerr << "--------------------------------" << endl;
    cerr << "-------- Test Add Edges --------" << endl;
    cerr << "--------------------------------" << endl;

    G.addEdge(0, 1) ;
    G.addEdge(1, 2) ;
    G.addEdge(2, 3) ;
    G.addEdge(3, 4) ;
    G.addEdge(4, 0) ;

    cerr << "G Dump:" << endl;
    G.dump() ;
    cerr << endl;
    
    // Test copy constructor by copying G into G2
    // Note: This will not keep them in the same order.
    cerr << "--------------------------------" << endl;
    cerr << "---- Test Copy Constructor -----" << endl;
    cerr << "--------------------------------" << endl;
    Graph G2 = Graph(G) ;
    cerr << "G2 Dump:" << endl;
    G2.dump() ;
    cerr << endl;

    // Try to assign G to itself.
    cerr << "--------------------------------" << endl;
    cerr << "---- Self Asignment Static -----" << endl;
    cerr << "--------------------------------" << endl;
    G.dump();
    G = G;
    cerr << "G Dump Post Assignment:" << endl;
    G.dump();
    
    // Test the neighbor iterator
    cerr << "--------------------------------" << endl;
    cerr << "---- Test Neighbor Iterator ----" << endl;
    cerr << "--------------------------------" << endl;
    printNeighbors(G, 0) ;
    printNeighbors(G, 3) ;
    cerr << endl << endl;

    // Test the edge iterator
    cerr << "--------------------------------" << endl;
    cerr << "------ Test Edge Iterator ------" << endl;
    cerr << "--------------------------------" << endl;
    printEdges(G) ;
    cerr << endl << endl;

    


    //////////////////////////////////////////////////////
    // Testing various edge cases to check for things   //
    // like exceptions.                                 //
    //////////////////////////////////////////////////////
    cerr << "********************************" << endl;
    cerr << "********** Edge Cases **********" << endl;
    cerr << "********************************" << endl;
    
    // This is to check the out of range exceptions we might get while
    // working with static classes.
    cerr << "--------------------------------" << endl;
    cerr << "-- Test NbIterator Edge Cases --" << endl;
    cerr << "--------------------------------" << endl;


    cerr << "> Non-existent Vertex's Neighbor Iterator:" << endl;
    try {
        cerr << "Trying to create nbIterator of 8 in G" << endl;
        Graph::NbIterator(&G, 8, false) ;
    } catch(std::exception& err) {
        cerr << err.what() << endl;
    } 
    cerr << endl;
 
    cerr << "> Attempt to iterate eyond edge:" << endl;

    cerr << "Iterate through normally around 0:" << endl;
    Graph::NbIterator endNbItr = G.nbEnd(0);
    Graph::NbIterator nbItr = G.nbBegin(0); 
    while(nbItr != endNbItr) {
        cerr << *nbItr << " ";
        nrItr++;
    }

    cerr << "Is nbItr at end?" << endl;
    cerr << !(nbItr != endNbItr) << endl;
    
    cerr << "Iterate." << endl;
    nbItr++;
    
    cerr << "Is nbItr still at end?" << endl;
    cerr << !(nbItr != endNbItr) << endl;
    cerr << endl;

    cerr << "> Attempt to dereference iterator at end." << endl;
    try {     
        cerr << *nbItr << endl;
    } catch (std::exception& err) {
        cerr << err.what() << endl;
    }
    cerr << endl;


    // 
    cerr << "--------------------------------" << endl;
    cerr << "---- Test EgItr Edge Cases -----" << endl;
    cerr << "--------------------------------" << endl;
    
    // EDGE ITERATOR TESTS 
    cerr << "> Attempt to iterate beyond end of edge iterator:" << endl;
    
    Graph::EgIterator endEgItr = G.egEnd();

    // First we have to iterate through the edge iterator.
    cerr << "Iterate through edge iterator" << endl;
    Graph::EgIterator egItr = G.egBegin(); 
    while(egItr != endEgItr) {
        std::pair<int, int> edge = *egItr;
        printf("(%u, %u) ", edge.first, edge.second);
        egItr++;
    }


    // Then lets make sure it'll properly iterate once it gets to the end.
    cerr << "Is egItr at end?" << endl;
    cerr << !(egItr != endEgItr) << endl;
    
    cerr << "Iterate." << endl;
    egItr++;
    
    cerr << "Is egItr still at end?" << endl;
    cerr << !(egItr != endEgItr) << endl;
    cerr << endl;


    cerr << "> Attempt to dereference iterator at end." << endl;
    try {     
        cerr << (*egItr).first << endl;
    } catch (std::exception& err) {
        cerr << err.what() << endl;
    }
    cerr << endl;





    ///////////////////////////////////////////////////
    // Testing Functionality for Dynamic Objects //////
    ///////////////////////////////////////////////////
    cerr << "********************************" << endl;
    cerr << "********* Dynamic Class ********" << endl;
    cerr << "********************************" << endl;


    cerr << "--------------------------------" << endl;
    cerr << "------ Test Constructor --------" << endl;
    cerr << "--------------------------------" << endl;

    Graph* Gptr1 = new Graph(5);
    cerr << "Gptr1:" << endl;
    Gptr1->dump();
    cerr << endl;


    cerr << "--------------------------------" << endl;
    cerr << "-------- Test Add Edges --------" << endl;
    cerr << "--------------------------------" << endl;

    // Add edges to dynamic object
    Gptr1->addEdge(3, 4);
    Gptr1->addEdge(1, 4);
    Gptr1->addEdge(0, 3);
    Gptr1->addEdge(0, 4);
    Gptr1->addEdge(0, 1);
    Gptr1->addEdge(1, 2);
    Gptr1->addEdge(2, 4);;

    cerr << "Gptr1 Dump:" << endl;
    Gptr1->dump();
    cerr << endl;


    // Check for Self Assignment with dynamic class
    cerr << "--------------------------------" << endl;
    cerr << "---- Self Asignment Dynamic ----" << endl;
    cerr << "--------------------------------" << endl;
    Gptr1 = Gptr1;
    cerr << "Gptr1 Dump:" << endl;
    Gptr1->dump();

    cerr << endl;

    //////////////////////////////////////////////////
    // Testing Functionality Combining Dynamic And  //
    // Static Objects.                              //
    //////////////////////////////////////////////////
    cerr << "********************************" << endl;
    cerr << "* Combining Dynamic and Static *" << endl;
    cerr << "********************************" << endl;

    cerr << "--------------------------------" << endl;
    cerr << "---- Stat->Dyn Copy Cstruct ----" << endl;
    cerr << "--------------------------------" << endl;

    cerr << "Static G: (GptrDS1 is nonexistent)" << endl;
    G.dump();
    cerr << endl;

    Graph* GptrDS1 = new Graph(G);
    
    cerr << "Dynamic GptrDS1 (copied):" << endl;
    GptrDS1->dump();
    cerr << endl;


    //////////////////////////////////////////////////
    // Delete all the dynamic memory.               //
    //////////////////////////////////////////////////
    cerr << "--------------------------------" << endl;
    cerr << "------- Deleting Pointer -------" << endl;
    cerr << "--------------------------------" << endl;

    cerr << "Deleting Gptr1..." << endl;
    delete Gptr1;
    cerr << "Deleting Gptr2..." << endl;
    //delete Gptr2;
    cerr << "Deleting GptrDS1..." << endl;
    delete GptrDS1;;
}

// Helper function for printing neighbors
void printNeighbors(Graph &G, int on) {
    
    printf("\nThe neighbors of vertex %u are:\n", on);
    
    Graph::NbIterator endNbItr = G.nbEnd(on);
    for(Graph::NbIterator itr = G.nbBegin(on); itr != endNbItr; itr++) {
        cerr << *itr << " ";
    }

}

// Helper function for pringing edges.
void printEdges(Graph &G) {

    printf("\nThe edges in the graph are:\n");

    Graph::EgIterator endEgItr = G.egEnd();
    for(Graph::EgIterator itr = G.egBegin(); itr != endEgItr; itr++) {
        std::pair<int, int> edge = *itr;
        printf("(%u, %u) ", edge.first, edge.second);
    }

}
