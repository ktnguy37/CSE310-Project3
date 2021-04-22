//
//  heap.cpp
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/6/21.
//

#include "heap.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
int parent(int i) {return floor((i-1) / 2);};
int left(int i) {return floor(2*i+2);};
int right(int i) {return floor(2*i+1);};

HEAP* initialize(int n) {
    HEAP *heap;
    heap = new HEAP[1]; //Dynamic Memory Allocation
    heap->capacity = n;
    heap->size = 0;
    heap->H = new pELEMENT [n+1]; // Dynamic Memory Allocation
//    for (int i = 0; i <= n+1;i++) {
//        heap->H[i] = NULL;
//    }
    return heap;
};

void printHeap(HEAP *heap) {
    cout<<"capacity="<<heap->capacity<<','<<' '<<"size="<<heap->size<<"\n";
    //Check if the heap contains at least 1 elements in order to print the heap
    if (heap->size > 0) {
        cout<<heap->H[0]->vertex;
        for (int i = 1; i < heap->size; i++) {
            cout<<", ";
            cout<<heap->H[i]->vertex;
        }
        cout<<"\n";
    }
    };

void swap(HEAP *heap,int x, int y) {
    pELEMENT temp = heap->H[x];
    heap->H[x] = heap->H[y];
    heap->H[y] = temp;
};

void min_Heapify(HEAP *heap,int index) {
    int smallest = index;
    if (left(index) < heap->size && heap->H[left(index)]->key < heap->H[index]->key) {
        smallest = left(index);
    }
    if (right(index) < heap->size && heap->H[right(index)]->key < heap->H[smallest]->key) {
        smallest = right(index);
    }

    if (smallest != index) {
        swap(heap,index,smallest);
        min_Heapify(heap, smallest);
    }

};

void buildHeap(HEAP *heap) {
    for (int i = parent(heap->size); i>= 0;i--) {
        min_Heapify(heap, i);
    }
};

int ExtractMin(HEAP *heap) {
    if (heap->size == 1) {
        heap->size--;
        min_Heapify(heap, 0);
        if (Flag == 1) {
            printf("Delete vertex %d, key=%12.4f\n",heap->H[0]->vertex,heap->H[0]->key);
        }
        int vertex = heap->H[0]->vertex;
        delete heap->H[0];
        return vertex;
    }
    if (heap->size == 0) {
        return -1;
    }
    int root = heap->H[0]->vertex;
    if (Flag == 1){
        printf("Delete vertex %d, key=%12.4f\n",heap->H[0]->vertex,heap->H[0]->key);
    }
    delete heap->H[0];
    heap->H[0] = heap->H[heap->size - 1];
    heap->size--;
    min_Heapify(heap, 0);
    return root;
};

int DecreaseKey(HEAP *heap,int pos, float newKey,pVERTEX V[]){
    if (pos < 0 || pos > heap->size || newKey >= heap->H[pos]->key) {
        //printf("Error in DecreaseKey\n");
        return 1;
    }
    if (Flag == 1) {
        printf("Decrease key of vertex %d, from %12.4f to %12.4f\n",heap->H[pos]->vertex,heap->H[pos]->key,newKey);
    }
    heap->H[pos]->key = newKey;
    MovingUp(heap, pos,V);
    return 0;
    
};
void Insert(HEAP *heap,pELEMENT element){
    int index = heap->size;
    heap->H[index] = element;
    heap->size++;
    if (Flag == 1) {
        printf("Insert vertex %d, key=%12.4f\n",element->vertex,element->key);
    }
    int Parent = parent(index);
    while (index != 0 && heap->H[Parent]->key > heap->H[index]->key ) {
        swap(heap,index,parent(index));
        index = parent(index);
    }
};

void MovingUp(HEAP *heap, int pos, pVERTEX V[]) {
    pELEMENT temp;
    int Parent = parent(pos);
    if (pos > 1 && heap->H[pos]->key < heap->H[Parent]->key) {
        temp = heap->H[pos];
        heap->H[pos] = heap->H[Parent];
        heap->H[Parent] = temp;
        
        V[heap->H[pos]->vertex]->pos = pos;
        V[heap->H[Parent]->vertex]->pos = Parent;
        
        MovingUp(heap, Parent,V);
    }
};

int findIndex(HEAP *heap,pNODE input) {
    int index = -1;
    for (int i = 0; i < heap->size;i++) {
        if (heap->H[i]->vertex == input->v) {
            index = i;
            return index;
        }
    }
    return index;
}

void deleteHeap(HEAP *heap) {
//    for (int i = 0; i <= heap->capacity;i++) {
//        delete heap->H[i];
//    }
    delete [] heap->H;
    delete heap;
}
