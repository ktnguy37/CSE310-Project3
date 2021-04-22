//
//  graph.cpp
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/8/21.
//

#include "graph.h"
#include <stddef.h>
#include <iostream>
using namespace std;

    Graph::Graph(int n,int m)
    {
        A = new pNODE[m+1]; //List of Nodes
        V = new pVERTEX[n+1];
        size  = m;
        sizeV = n;
        numberVertices = n;
        directed = true;
        for (int i = 0; i <= size; i++) {
            A[i] = NULL;
        }
        for (int i = 0; i <= numberVertices;i++) {
            V[i] = NULL;
        }
    }
    Graph::Graph()
    {
        numberVertices = 0;
    }
//    ~DiaGraph() {
//        for (int i = 0; i < sizeof(A);i++ ) {
//            delete [] A[i];
//            delete A;
//        }
//    };
    
    void Graph::addDirectedEdge(int u, int v, float w) {
        if (A[u] != NULL) {
            pNODE temp = new NODE();
            temp->v = v;
            temp->w = w;
            temp->next = A[u];
            A[u] = temp;
        } else {
            pNODE temp = new NODE();
            temp->v = v;
            temp->w = w;
            temp->next = NULL;
            A[u] = temp;
            
        }
    }
    
    void Graph::addUnDirectedEdge(int u, int v, float w) {
        addDirectedEdge(u, v, w);
        addDirectedEdge(v, u, w);
    }
    
    void Graph::displayGraph()
    {
       
        for (int i = 1; i <= size; i++) {
            pNODE temp = A[i];
            while (temp != NULL) {
                cout << "(" << i << ", " << temp->v
                    << ", " << temp->w << ") ";
                temp = temp->next;
                cout << endl;
            }
            
        }
      
        
        
    }

