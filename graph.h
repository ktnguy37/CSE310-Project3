//
//  graph.h
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/8/21.
//

#ifndef graph_h
#define graph_h
#include <string>
using namespace std;
typedef struct TAG_NODE {
    int v;
    float w;
    TAG_NODE *next;
} NODE;

typedef NODE *pNODE;

typedef struct TAG_VERTEX {
    string color;
    int pi;
    float d;
    int pos; //index in heap array
} VERTEX;

typedef VERTEX *pVERTEX;

class Graph
{
public:
    pNODE* A;
    pVERTEX* V;
    int size;
    int sizeV;
    int numberVertices;
    bool directed;
    Graph();
    Graph(int n,int m);
    void addDirectedEdge(int u, int v, float w);
    void addUnDirectedEdge(int u, int v, float w);
    void displayGraph();
};

#endif /* graph_h */
