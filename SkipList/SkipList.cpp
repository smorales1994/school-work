//
//  SkipList.cpp
//

#include "SkipList.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
// TODO: constructor
template <class T>
SkipList<T>::SkipList()
{
    head = new Node<T> (T(), maxHeight);

    height = 1;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
// TODO: destructor
template <class T>
SkipList<T>::~SkipList()
{
    makeEmpty();

    delete head;
}
#endif

/* **************************************************************** */

#if FIND || ALL
// TODO: find() method
template <class T>
bool SkipList<T>::find(const T &x) const
{
    Node<T> *node = head;

    if (!isEmpty())
    {
        for (int i = height - 1; i >= 0; i--)
        {
            while (node -> next[i] != nullptr && node -> next[i] -> data < x)
            {
                node = node -> next[i];
            }
        }

        return node -> next[0] -> data == x;
    }

    return false;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
// TODO: insert() method
template <class T>
void SkipList<T>::insert(const T &x)
{
    Node<T> **update = new Node<T> *[maxHeight];
    Node<T> *node = head;

    for (int i = height - 1; i >= 0; i--)
    {
        while (node -> next[i] != nullptr && node -> next[i] -> data < x)
        {
            node = node -> next[i];
        }

        update[i] = node;
    }

    node = node -> next[0];

    if (node == nullptr || node -> data != x)
    {
        node = head;

        int newHeight = randomLevel();

        if (newHeight > height)
        {
            for (int i = height; i < newHeight; i++)
            {
                update[i] = node;
            }

            height = newHeight;
        }

        node = new Node<T> (x, newHeight);

        for (int i = 0; i < newHeight; i++)
        {
            node -> next[i] = update[i] -> next[i];
            update[i] -> next[i] = node;
        }
    }

    delete[] update;
}
#endif

/* **************************************************************** */

#if REMOVE || ALL
// TODO: remove() method
template <class T>
void SkipList<T>::remove(const T &x)
{
    Node<T> **update = new Node<T> *[maxHeight];
    Node<T> *node = head;

    for (int i = height - 1; i >= 0; i--)
    {
        while (node -> next[i] != nullptr && node -> next[i] -> data < x)
        {
            node = node -> next[i];
        }

        update[i] = node;
    }

    node = node -> next[0];

    if (node != nullptr && node -> data == x)
    {
        for (int i = 0; i < height; i++)
        {
            if (update[i] -> next[i] != node)
            {
                break;
            }

            update[i] -> next[i] = node -> next[i];
        }

        delete node;

        while (height > 1 && head -> next[height - 1] == nullptr)
        {
            height--;
        }
    }

    delete[] update;
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty() method
template <class T>
bool SkipList<T>::isEmpty() const
{
    Node<T> *node = head;

    for (int i = 0; i < height; i++)
    {
        if (node -> next[i] != nullptr)
        {
            return false;
        }
    }

    return true;
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template <class T>
void SkipList<T>::makeEmpty()
{
    while (head != nullptr)
    {
        Node<T> *temp = head -> next[0];

        delete head;

        head = temp;
    }

    head = new Node<T> (T(), maxHeight);

    height = 1;
}
#endif

/* **************************************************************** */

#if RANDOMLEVEL || ALL
// TODO: randomLevel() method
template <class T>
int SkipList<T>::randomLevel()
{
    int newHeight = 1;

    while (getRandomNumber() <= .5 && newHeight < height + 1 && newHeight < maxHeight)
    {
        newHeight++;
    }

    return newHeight;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
// Do NOT modify anything below this line
/* **************************************************************** */

#ifndef BUILD_LIB
// random number generator
template <class T>
double SkipList<T>::getRandomNumber()
{
    static int i = 0;
    static double a[10] = {0.32945,0.15923,0.12982,0.16250,0.36537,0.64072,0.27597,0.83957,0.75531,0.22502};
    
    return a[(i++)%10];
}


// printList() method
template <class T>
void SkipList<T>::printList()
{
    Node<T> *n = head;
    
    if (isEmpty())
    {
        std::cout << "Empty List" << std::endl;
    } else {
        while(n->next[0] != nullptr)
        {
            n = n->next[0];
            // Print node data
            std::cout << "Node " << n->data << " height " << n->height << ": ";
            
            // Print levels
            for (int i=(n->height - 1); i >= 0; i--) {
                std::cout << "Level " << i << " -> ";
                if (n->next[i] != nullptr) {
                    std::cout << n->next[i]->data;
                } else {
                    std::cout << "nullptr";
                }
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
#endif

template class SkipList<int>;


