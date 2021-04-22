//
//  heap.h
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/6/21.
//

#ifndef heap_h
#define heap_h

#include "graph.h"

typedef struct TAG_ELEMENT {
    int vertex;
    float key;
} ELEMENT;

typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT *H;
    
} HEAP;

extern int Flag;

HEAP* initialize(int n);
void printHeap(HEAP *heap);
void WriteHeap(HEAP *heap);
void Insert(HEAP *heap,pELEMENT element);
int ExtractMin(HEAP *heap);
int DecreaseKey(HEAP *heap,int index, float value, pVERTEX V[]);
void min_Heapify(HEAP *heap, int index);
void buildHeap(HEAP *heap);
void MovingUp(HEAP *heap, int pos,pVERTEX V[]);
int findIndex(HEAP *heap,pNODE input);
void deleteHeap(HEAP *heap);
#endif /* heap_h */
