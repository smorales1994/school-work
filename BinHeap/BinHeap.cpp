//
//  BinHeap.cpp
//

#include "BinHeap.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
template <class T>
BinHeap<T>::BinHeap()
{
    // TODO: Allocate initial heap array and store sentinel value
    heapSize = 0;
    maxSize = 1;

    heapArray = new T[2];
    heapArray[0] = -1;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
template <class T>
BinHeap<T>::~BinHeap()
{
    // TODO: Deallocate heap array
    delete[] heapArray;
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
template <class T>
bool BinHeap<T>::isEmpty()
{
    // TODO: isEmpty() method
    return heapSize == 0;
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template <class T>
void BinHeap<T>::makeEmpty()
{
    delete[] heapArray;

    heapSize = 0;
    maxSize = 1;

    heapArray = new T[2];
    heapArray[0] = -1;
}
#endif

/* **************************************************************** */

#if RESIZEARRAY || ALL
template <class T>
void BinHeap<T>::resizeArray(int newSize)
{
    // TODO: resizeArray() method
    T* newHeapArray = new T[newSize + 1];

    newHeapArray[0] = -1;

    for (int i = 1; i <= heapSize; i++)
    {
        newHeapArray[i] = heapArray[i];
    }

    delete[] heapArray;

    heapArray = newHeapArray;

    maxSize = newSize;
}
#endif

/* **************************************************************** */

#if LEFTCHILDINDEX || ALL
template <class T>
int BinHeap<T>::leftChildIndex(int idx)
{
    // TODO: leftChildIndex() method
    return 2 * idx;
}
#endif

/* **************************************************************** */

#if RIGHTCHILDINDEX || ALL
template <class T>
int BinHeap<T>::rightChildIndex(int idx)
{
    // TODO: rightChildIndex() method
    return (2 * idx) + 1;
}
#endif

/* **************************************************************** */

#if PARENTINDEX || ALL
template <class T>
int BinHeap<T>::parentIndex(int idx)
{
    // TODO: parentIndex() method
    return idx / 2;
}
#endif

/* **************************************************************** */

#if MINCHILD || ALL
template <class T>
int BinHeap<T>::minChild(int idx)
{
    // TODO: minChild() method
    if (rightChildIndex(idx) <= heapSize && leftChildIndex(idx) <= heapSize)
    {
        if (heapArray[rightChildIndex(idx)] < heapArray[leftChildIndex(idx)])
        {
            return rightChildIndex(idx);
        }

        else
        {
            return leftChildIndex(idx);
        }
    }

    else if (rightChildIndex(idx) <= heapSize && leftChildIndex(idx) > heapSize)
    {
        return rightChildIndex(idx);
    }

    else if (leftChildIndex(idx) <= heapSize && rightChildIndex(idx) > heapSize)
    {
        return leftChildIndex(idx);
    }

    else
    {
        return -1;
    }
}
#endif

/* **************************************************************** */

#if INSERT || ALL
template <class T>
void BinHeap<T>::insert(const T &x)
{
    // TODO: insert() method
    if (heapSize == maxSize)
    {
        resizeArray(maxSize * 2);
    }

    heapArray[++heapSize] = x;

    percolateUp(heapSize);
}
#endif

/* **************************************************************** */

#if REMOVEMIN || ALL
template <class T>
T BinHeap<T>::removeMin()
{
    // TODO: removeMin() method
    if (!isEmpty())
    {
        T minNode = heapArray[1];

        heapArray[1] = heapArray[heapSize];

        heapSize--;

        percolateDown(1);

        if (heapSize < maxSize / 3.0)
        {
            resizeArray(maxSize / 2);
        }

        return minNode;
    }

    return -1;
}
#endif

/* **************************************************************** */

#if PERCOLATEUP || ALL
template <class T>
void BinHeap<T>::percolateUp(int idx)
{
    // TODO: percolateUp() method
    while (heapArray[idx] < heapArray[parentIndex(idx)])
    {
        T tempNode = heapArray[idx];

        int tempIdx = parentIndex(idx);

        heapArray[idx] = heapArray[parentIndex(idx)];
        heapArray[parentIndex(idx)] = tempNode;

        idx = tempIdx;
    }
}
#endif

/* **************************************************************** */

#if PERCOLATEDOWN || ALL
template <class T>
void BinHeap<T>::percolateDown(int idx)
{
    // TODO: percolateDown() method
    while (minChild(idx)!= -1 && (heapArray[idx] > heapArray[minChild(idx)]))
    {
        T tempNode = heapArray[idx];

        int tempIdx = minChild(idx);

        heapArray[idx] = heapArray[minChild(idx)];
        heapArray[minChild(idx)] = tempNode;

        idx = tempIdx;
    }
}
#endif

/* **************************************************************** */

#if BUILDHEAP || ALL
template <class T>
void BinHeap<T>::buildHeap(const T *arr, int size)
{
    // TODO: buildHeap() method
    resizeArray(size);

    heapSize = size;

    for (int i = 1; i <= heapSize; i++)
    {
        heapArray[i] = arr[i - 1];

    }

    for (int i = (heapSize / 2); i >= 1; i--)
    {
        percolateDown(i);
    }
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/* Do NOT modify anything below this line                           */
/* **************************************************************** */

#ifndef BUILD_LIB
template <class T>
void BinHeap<T>::printHeap()
{
    std::stringstream ss;
    printHeapToStream(ss);
    std::cout << ss.str();
}


template <class T>
void BinHeap<T>::printHeapToStream(std::stringstream& ss)
{
    ss << "  Current array size: " << maxSize << std::endl;
    ss << "  Current heap size: " << heapSize << std::endl;
    
    if (!isEmpty()) {
        ss << "  Heap Elements: ";
        // Print heap array
        for (int i = 1; i <= heapSize; i++) {
            ss << heapArray[i] << " ";
        }
    }
    else {
        ss << "  Heap is empty";
    }
    ss << std::endl << std::endl;
}
#endif

template class BinHeap<int>;
