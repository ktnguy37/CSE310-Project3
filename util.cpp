//
//  util.cpp
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/15/21.
//

#include "util.h"
#include "heap.h"
#include "graph.h"
#include <climits>
#include <vector>
#include <iostream>
#include <sstream>
int dijkstra_SP(Graph G,int s, int t) {
    HEAP *heap = new HEAP;
    heap = initialize(G.sizeV);
    for (int i = 0; i <= G.sizeV; i++) {
        pVERTEX temp = new VERTEX;
        temp->color = "white";
        temp->d = INT_MAX;
        temp->pi = 0;
        G.V[i] = temp;
    }
    G.V[s]->d = 0.0;
    G.V[s]->color = "black";
    
    pELEMENT tempS = new ELEMENT;
    tempS->vertex = s;
    tempS->key = G.V[s]->d;
    Insert(heap, tempS);
    while (heap->size > 0) {
        int u = ExtractMin(heap);
        G.V[u]->color = "black";
        if (u == t) {
            deleteHeap(heap);
            return 0;
        }
        
        pNODE tempV = G.A[u];
        while (tempV != NULL) {
            if (G.V[tempV->v]->color.compare("white") == 0) {
                G.V[tempV->v]->d = G.V[u]->d + tempV->w;
                pELEMENT tempElement = new ELEMENT;
                tempElement->vertex = tempV->v;
                tempElement->key = G.V[tempV->v]->d;
                G.V[tempV->v]->color = "grey";
                G.V[tempV->v]->pi = u;
                Insert(heap, tempElement);
            }
            else if (G.V[tempV->v]->d > G.V[u]->d + tempV->w) {
                G.V[tempV->v]->d = G.V[u]->d + tempV->w;
                G.V[tempV->v]->pi = u;
                int index = findIndex(heap, tempV);
                DecreaseKey(heap, index, G.V[tempV->v]->d, G.V);
                    
            }
            tempV = tempV->next;
        }
        
    }
    deleteHeap(heap);
    return 1;
}
vector<int> findRoute(Graph G, int s, int t) {
    vector<int>path;
    if (s == t) {
        path.push_back(s);
        return path;
    }
    path = findRoute(G, s, G.V[t]->pi);
    path.push_back(t);
    return path;
    
}
void printPathWeight(Graph G, int t) {
    //printf("The path weight is: %12.4f\n",G.V[t]->d);
    printf("The path weight is: %12.4f\n",G.V[t]->d);
}

vector<string>split_string(string input){
    vector<string> result;
    istringstream stm(input);
    string token;
    
    while( stm >> token ) result.push_back(token) ;
    return result;
}

void printPath(vector<int>route) {
    cout<<"<"<<route.at(0)<<", ";
    
    for (int i = 1; (unsigned) i < (unsigned) route.size() -1; i++) {
        cout<<route.at(i)<<", ";
    }
    cout<<route.at(route.size()-1)<<">";
    cout<<"\n";
}
