//
//  IntArrayStack.cpp
//

#include "IntArrayStack.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// TODO: Constructor
IntArrayStack::IntArrayStack()
{
    top = -1;
    capacity = 1;
    stack = new int[capacity];

    for (int i = 0; i < capacity; i++)
    {
        stack[i] = 0;
    }
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// TODO: Destructor
IntArrayStack::~IntArrayStack()
{
    delete[] stack;
}
#endif

/* **************************************************************** */

#if PUSH || ALL
// TODO: push()
void IntArrayStack::push(int x)
{
    if (++top == capacity)
    {
        resize(capacity * 2);
    }

    stack[top] = x;
}
#endif

/* **************************************************************** */

#if POP || ALL
// TODO: pop()
int IntArrayStack::pop()
{
    if (isEmpty())
    {
        return -1;
    }

    int topElem = stack[top--];

    if (top < (capacity / 3) && capacity != 1)
    {
        resize((capacity / 2));
    }

    return topElem;
}
#endif

/* **************************************************************** */

#if PEEK || ALL
// TODO: peek()
int IntArrayStack::peek()
{
    if (isEmpty())
    {
        return -1;
    }

    return stack[top];
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty()
bool IntArrayStack::isEmpty()
{
    return top == - 1;
}
#endif

/* **************************************************************** */

#if EMPTYSTACK || ALL
// TODO: emptyStack()
void IntArrayStack::emptyStack()
{
    top = -1;
    capacity = 1;

    for (int i = 0; i < capacity; i++)
    {
        stack[i] = 0;
    }
}
#endif

/* **************************************************************** */

#if RESIZE || ALL
// TODO: resize()
void IntArrayStack::resize(int newCapacity)
{
    capacity = newCapacity;

    int *newStack = new int[newCapacity];

    for (int i = 0; i < capacity; i++)
    {
        newStack[i] = stack[i];
    }

    delete[] stack;

    stack = newStack;
}
#endif

/* **************************************************************** */
// Do NOT modify anything below this line
// Do NOT use these methods in your implementation of your data
// structure.  They are included here to support the unit tests.
/* **************************************************************** */

#ifndef BUILD_LIB
void IntArrayStack::printStack()
{
    std::cout << std::endl;
    std::cout << "Current array size: " << capacity << std::endl;
    std::cout << "Number of ints in stack: " << top+1 << std::endl;
    for (int i=top; i >= 0; i--)
    {
        std::cout << stack[i] << " ";
    }
    std::cout << std::endl;
}


// Do NOT use this method in your implementation
int IntArrayStack::getCapacity()
{
    return capacity;
}


// Do NOT use this method in your implementation
int IntArrayStack::getSize()
{
    return top+1;
}


// Do NOT use this method in your implementation
int IntArrayStack::getTop()
{
    return top;
}


// Do NOT use this method in your implementation
void IntArrayStack::toArray(int* arr)
{
    for (int i=0; i < capacity; i++)
    {
        arr[i] = stack[i];
    }
}
#endif

/* **************************************************************** */


