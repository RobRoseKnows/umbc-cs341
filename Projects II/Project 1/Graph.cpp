/*
 * File:    Graph.cpp
 * Author:  Robert Rose
 * Date:    2/17/17
 * E-mail:  robrose2@umbc.edu
 *
 */

#include "Graph.h"
#include <iostream> 
#include <stdio.h> // This allows me to use printf

using namespace std;


Graph::Graph(int n) {

    if(n <= 0) {
        throw std::out_of_range("OUT OF RANGE: Invalid graph size (n <= 0) in constructor");
    }

    m_size = n ;
    m_adjLists = new AdjListNode*[n] ;

}


Graph::Graph(const Graph& G) {

    m_size = G.m_size ;
    m_adjLists = new AdjListNode*[m_size] ;

    for(int i = 0; i < m_size; i++) {
        
        AdjListNode *on = G.m_adjLists[i] ;
        
        while(on != NULL) {

            m_adjLists[i] = new AdjListNode(on->m_vertex, m_adjLists[i]) ;
            on = on->next ;

        }

    }

}


Graph::~Graph() {
/*
    for(int i = 0; i < size(); i++) {
        AdjListNode* on = m_adjLists[i] ;
        while(on != NULL) {
            AdjListNode* nextTemp = on->next;
            delete on;
            on = nextTemp;
        }
    }
*/
    delete [] m_adjLists;
}


const Graph& Graph::operator=(const Graph& rhs) {

    // Check for self assignment
    if(&rhs == this) {
        return *this;
    } else {
        
        // Get rid of the current adjacency list.
        delete [] m_adjLists;

        // Set up the new adjacency list.
        m_size = rhs.m_size;
        m_adjLists = new AdjListNode*[m_size];

        // Go through the right hand side verticies.
        for(int i = 0; i < m_size; i++) {
            AdjListNode *on = rhs.m_adjLists[i] ;

            // Copy the linked list
            while(on != NULL) {
                m_adjLists[i] = new AdjListNode(on->m_vertex, m_adjLists[i]) ;
                on = on->next ;
            }
        }

    }


}


int Graph::size() {

    return m_size ;

}


void Graph::addEdge(int u, int v) {

    m_adjLists[u] = new AdjListNode(v, m_adjLists[u]);
    m_adjLists[v] = new AdjListNode(u, m_adjLists[v]);

}


void Graph::dump() {

    printf("Dump out graph (size = %u):\n", m_size) ;

    for(int i = 0; i < m_size; i++) {

        // Print out what node we're using as root.
        printf("[ %u]:", i) ;

        // Keep track of what node we're iterating through.
        AdjListNode *on = m_adjLists[i];

        while(on != NULL) {
            // Print out list
            printf(" %u", on->m_vertex) ;
            on = on->next ;
        }

        cout << endl ;
    
    }

}



////////////////////////////////////////////////////
// Begin EgIterator Inner Class
////////////////////////////////////////////////////

Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd) {
    m_Gptr = Gptr;
    
    if(!isEnd) {
        m_source = 0;
        m_where = m_Gptr->m_adjLists[m_source];
    } else {
        m_source = m_Gptr->m_size;
        m_where = NULL;
    }
}


bool Graph::EgIterator::operator!= (const EgIterator& rhs) {
    return m_source != rhs.m_source;
}


void Graph::EgIterator::operator++ (int dummy) {

    // If we're less than or eqaul to the number of verticies, we are at the
    // the end of the edges, so just exit the function.
    if(m_source >= m_Gptr->m_size) {
        return;
    }


    if(m_where == NULL) {
        m_source++;
        
        // We use this same conditional earlier, but I decided to check again
        // so we don't get an array out of bounds error when setting m_where
        // on the last row.
        if(m_source >= m_Gptr->m_size) {
        
            m_where = NULL;
        
        } else {
            
            m_where = m_Gptr->m_adjLists[m_source];
        
        }

    } else {

        m_where = m_where->next;

    }


    // We're going to recursively call the iterate operator until we find a
    // valid edge.
    if(m_where == NULL || m_source > m_where->m_vertex) {
        
        (*this)++;
    
    }

}


// Dereference the edge iterator. If the iterator is at the end, it throws an
// out_of_range exception.
std::pair<int, int> Graph::EgIterator::operator*() {
    if(m_source < m_Gptr->m_size) {
        return std::pair<int, int>(m_source, m_where->m_vertex);
    } else {
        throw std::out_of_range("OUT OF RANGE: Cannot derefference iterator. EgIterator at end.");
    }
}

////////////////////////////////////////////////////
// END EgIterator Inner Class
////////////////////////////////////////////////////



Graph::EgIterator Graph::egBegin() {
    return EgIterator(this, false) ;
}


Graph::EgIterator Graph::egEnd() {
    return EgIterator(this, true) ;
}



////////////////////////////////////////////////////
// BEGIN NbIterator Inner Class
////////////////////////////////////////////////////

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd) {

    // Check to make sure the vertex is in the graph.
    if(v >= Gptr->size()) {
        throw std::out_of_range("OUT OF RANGE: NbIterator constructor: that vertex does not exist.");
    }

    m_Gptr = Gptr ;
    m_source = v ;

    if(!isEnd) {
        m_where = Gptr->m_adjLists[v] ;
    } else {
        m_where = NULL ;
    }
}


// False equality opertor.
bool Graph::NbIterator::operator!= (const NbIterator& rhs) {

    return m_where != rhs.m_where ;

}


// Iterate operator
void Graph::NbIterator::operator++ (int dummy) {

    if(m_where != NULL) {
        m_where = m_where->next;
    }

}


// Derefference operator
int Graph::NbIterator::operator*() {

    // Check to make sure the iterator isn't at the end.
    if(m_where != NULL) {
        return m_where->m_vertex;
    } else {
        throw std::out_of_range("OUT OF RANGE: Cannot derefference iterator. NbIterator at end.") ;
    }

}

////////////////////////////////////////////////////
// END NbIterator Inner Class
////////////////////////////////////////////////////


// Returns an iterator at the beginning of a neighbor iteration.
Graph::NbIterator Graph::nbBegin(int v) {
    return NbIterator(this, v, false) ;
}


// Returns an iterator at the end of a nieghbor iteration (e.g. where = NULL)
Graph::NbIterator Graph::nbEnd(int v) {
    return NbIterator(this, v, true) ;
}



////////////////////////////////////////////////////
// BEGIN AdjListNode Inner Class
////////////////////////////////////////////////////

Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr) {
    
    m_vertex = v ;
    next = ptr;

}

////////////////////////////////////////////////////
// END AdjListNode Inner Class
////////////////////////////////////////////////////




