//
//  BinHeap.h
//

#ifndef _BINHEAP_H_
#define _BINHEAP_H_

#include <iostream>
#include <sstream>

template <class T>
class BinHeap
{
public:
    // Constructor, destructor
    BinHeap();
    ~BinHeap();
    
    // Public interface
    bool isEmpty();
    void makeEmpty();
    void insert(const T & x);
    T removeMin();
    void buildHeap(const T* arr, int size);
    void printHeap();
    void printHeapToStream(std::stringstream& ss);
    
    // Private fields
    T* heapArray;
    int maxSize;
    int heapSize;
    
    // Private methods
    void resizeArray(int newSize);
    int leftChildIndex(int idx);
    int rightChildIndex(int idx);
    int parentIndex(int idx);
    int minChild(int idx);
    void percolateUp(int idx);
    void percolateDown(int idx);
};

#endif
