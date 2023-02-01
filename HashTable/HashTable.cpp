//
//  HashTable.cpp
//

#include "HashTable.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
HashTable::HashTable(int tableSize)
{
    // TODO: Constructor
    table = new Node* [tableSize];

    for (int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }

    size = tableSize;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
HashTable::~HashTable()
{
    // TODO: Destructor
    for (int i = 0; i < size; i++)
    {
        Node *head = table[i];

        while (head != nullptr)
        {
            Node *tempNode = head -> next;

            delete head;

            head = tempNode;
        }
    }

    delete[] table;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
void HashTable::insert(std::string x)
{
    // TODO: insert() method
    if (!find(x))
    {
        Node *node = new Node(x);

        if (table[hash(x)] == nullptr)
        {
            table[hash(x)] = node;
        }

        else
        {
            Node *tempNode = table[hash(x)];

            table[hash(x)] = node;
            table[hash(x)] -> next = tempNode;
        }
    }
}
#endif

/* **************************************************************** */

#if FIND || ALL
bool HashTable::find(std::string x)
{
    // TODO: find() method
    Node *head = table[hash(x)];

    while (head != nullptr)
    {
        if (head -> data == x)
        {
            return true;
        }

        head = head -> next;
    }

    return false;
}
#endif

/* **************************************************************** */

#if REMOVE || ALL
void HashTable::remove(std::string x)
{
    // TODO: remove() method
    Node *head = table[hash(x)];
    Node *prevNode = head;

    while (head != nullptr)
    {
        if (head -> data == x)
        {
            if (prevNode == head)
            {
                table[hash(x)] = head -> next;
            }

            else
            {
                prevNode -> next = head -> next;
            }

            delete head;

            break;
        }

        prevNode = head;

        head = head -> next;
    }
}
#endif

/* **************************************************************** */

#if LOADFACTOR || ALL
float HashTable::loadFactor()
{
    // TODO: loadFactor() method
    float count = 0;

    for (int i = 0; i < size; i++)
    {
        Node *head = table[i];

        while (head != nullptr)
        {
            head = head -> next;

            count++;
        }
    }

    return count / size;
}
#endif

/* **************************************************************** */

#if MAXCHAINLENGTH || ALL
void HashTable::maxChainLength(int &maxLength, int &maxSlotIndex)
{
    // TODO: maxChainLength() method
    maxLength = maxSlotIndex = 0;

    for (int i = 0; i < size; i++)
    {
        int count = 0;

        Node *head = table[i];

        while (head != nullptr)
        {
            head = head -> next;

            count++;
        }

        if (count > maxLength)
        {
            maxLength = count;
            maxSlotIndex = i;
        }
    }
}
#endif

/* **************************************************************** */

#if NUMEMPTYSLOTS || ALL
int HashTable::numEmptySlots()
{
    // TODO: numEmptySlots() method
    int emptySlots = 0;

    for (int i = 0; i < size; i++)
    {
        Node *head = table[i];

        if (head == nullptr)
        {
            emptySlots++;
        }
    }

    return emptySlots;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/* Do NOT modify anything below this line                           */
/* **************************************************************** */

#ifndef BUILD_LIB
unsigned int HashTable::hash(std::string x) {
    unsigned int hashCode = 0;
    std::string::iterator it;
    for (it=x.begin(); it < x.end(); it ++) {
        hashCode = *it + (hashCode << 5) - hashCode;
    }
    return hashCode % size;
}


void HashTable::printHashTable() {
    std::stringstream ss;
    printHashTableToStream(ss);
    std::cout << ss.str();
}


void HashTable::printHashTableToStream(std::stringstream& ss) {
    Node* node;
    // Iterate over table
    for (int i = 0; i < size; i++) {
        ss << "[" << i << "]: ";
        // Iterate over list
        node = table[i];
        while (node != nullptr) {
            ss << node->data << " -> ";
            node = node->next;
        }
        ss << "nullptr" << std::endl;
    }
}
#endif
