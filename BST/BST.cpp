//
//  BST.cpp
//

#include "BST.h"
#include "Flags.h"

/* **************************************************************** */
#if ALL || CONSTRUCTOR
template <class T>
BST<T>::BST()
{
    // TODO: Initialize root
    root = nullptr;

    numNodes = 0;
}
#endif

/* **************************************************************** */
#if ALL || DESTRUCTOR
template <class T>
BST<T>::~BST()
{
    // TODO: Remove any nodes
    makeEmpty();
}
#endif

/* **************************************************************** */
#if ALL || ISEMPTY
// TODO: isEmpty() method
template <class T>
bool BST<T>::isEmpty()
{
    return root == nullptr;
}
#endif

/* **************************************************************** */
#if ALL || FIND
// TODO: find() method
template <class T>
bool BST<T>::find(const T &x)
{
    return findNode(root, x);
}
#endif

/* **************************************************************** */
#if ALL || FINDMIN
// TODO: findMin() method
template <class T>
const T &BST<T>::findMin()
{
    if (!isEmpty())
    {
        return findMinNode(root) -> data;
    }

    throw 1;
}
#endif

/* **************************************************************** */
#if ALL || FINDMAX
// TODO: findMax() method
template <class T>
const T &BST<T>::findMax()
{
    if (!isEmpty())
    {
        return findMaxNode(root) -> data;
    }

    throw 1;
}
#endif

/* **************************************************************** */
#if ALL || INSERT
// TODO: insert() method
template <class T>
void BST<T>::insert(const T &x)
{
    if (!isEmpty())
    {
        insertNode(root, x);
    }

    else
    {
        root = new Node<T> (x);

        numNodes++;
    }
}
#endif

/* **************************************************************** */
#if ALL || REMOVE
// TODO: remove() method
template <class T>
void BST<T>::remove(const T &x)
{
    Node<T> *node = findNode(root, x);

    if (node != nullptr)
    {
        if (node -> left == nullptr && node -> right == nullptr)
        {
            Node<T> *parent = findParentOf(node -> data);

            if (parent != nullptr)
            {
                if (parent -> left == node)
                {
                    parent -> left = nullptr;
                }

                else
                {
                    parent -> right = nullptr;
                }

                delete node;

                numNodes--;
            }

            else
            {
                delete node;

                root = nullptr;

                numNodes--;
            }
        }

        else if (node -> left != nullptr && node -> right == nullptr)
        {
            Node <T> *child = node -> left;

            node -> data = child -> data;
            node -> left = child -> left;
            node -> right = child -> right;

            delete child;

            numNodes--;
        }

        else if (node -> right != nullptr & node -> left == nullptr)
        {
            Node<T> *child = node -> right;

            node -> data = child -> data;
            node -> left = child -> left;
            node -> right = child -> right;

            delete child;

            numNodes--;
        }

        else if (node -> left != nullptr && node -> right != nullptr)
        {
            Node<T> *successor = findSuccessor(node);

            int successorVal = successor -> data;

            remove(successor -> data);

            node -> data = successorVal;
        }
    }
}
#endif

/* **************************************************************** */
#if ALL || MAKEEMPTY
// TODO: makeEmpty() method
template <class T>
void BST<T>::makeEmpty()
{
    removeAllNodes(root);

    root = nullptr;

    numNodes = 0;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/*  Private methods                                                 */
/* **************************************************************** */
#if ALL || FINDNODE
// TODO: findNode() private method
template <class T>
Node<T> *BST<T>::findNode(Node<T> *node, const T &x)
{
    if (node == nullptr || x == node -> data)
    {
        return node;
    }

    else if (x < node -> data)
    {

        return findNode(node -> left, x);

    }

    else
    {
        return findNode(node -> right, x);
    }
}
#endif

/* **************************************************************** */
#if ALL || FINDMINNODE
// TODO: findMinNode() private method
template <class T>
Node<T> *BST<T>::findMinNode(Node<T> *node)
{
    if (!isEmpty())
    {
        if (node -> left == nullptr)
        {
            return node;
        }

        else
        {
            return findMinNode(node -> left);
        }
    }

    return nullptr;
}
#endif

/* **************************************************************** */
#if ALL || FINDMAXNODE
// TODO: findMaxNode() private method
template <class T>
Node<T> *BST<T>::findMaxNode(Node<T> *node)
{
    if (!isEmpty())
    {
        if (node -> right == nullptr)
        {
            return node;
        }

        else
        {
            return findMaxNode(node -> right);
        }
    }

    return nullptr;
}
#endif

/* **************************************************************** */
#if ALL || INSERTNODE
// TODO: insertNode() private method
template <class T>
Node<T> *BST<T>::insertNode(Node<T> *node, const T &x)
{
    if (node == nullptr)
    {
        node = new Node<T> (x);

        numNodes++;
    }

    else if (x == node -> data)
    {
        node -> data = x;
    }

    else if (x < node -> data)
    {
        node -> left = insertNode(node -> left, x);
    }

    else
    {
        node -> right = insertNode(node -> right, x);
    }

    return node;
}
#endif

/* **************************************************************** */
#if ALL || FINDSUCCESSOR
// TODO: findSuccessor() private method
template <class T>
Node<T> *BST<T>::findSuccessor(Node<T> *node)
{
    Node<T> *rSubTree = node -> right;

    if (rSubTree != nullptr)
    {
        while (rSubTree -> left != nullptr)
        {
            rSubTree = rSubTree -> left;
        }

        return rSubTree;
    }

    return nullptr;
}
#endif

/* **************************************************************** */
#if ALL || FINDPARENTOF
// TODO: findParentOf() private method
template <class T>
Node<T> *BST<T>::findParentOf(const T &x)
{
    Node<T> *node = root;

    if (find(x) && node -> data != x)
    {
        while (node != nullptr)
        {
            if ((node -> left != nullptr && node -> left -> data == x) || (node -> right != nullptr && node -> right -> data == x))
            {
               return node;
            }

            else
            {
                if (x > node -> data)
                {
                    node = node -> right;
                }

                else
                {
                    node = node -> left;
                }
            }
        }
    }

    return nullptr;
}
#endif

/* **************************************************************** */
#if ALL || REMOVEALLNODES
// TODO: removeAllNodes() private method
template <class T>
void BST<T>::removeAllNodes(Node<T> *node)
{
    if (node != nullptr)
    {
        if (node -> left != nullptr)
        {
            removeAllNodes(node -> left);
        }

        if (node -> right != nullptr)
        {
            removeAllNodes(node -> right);
        }

        delete node;

        numNodes--;
    }
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/* Do NOT modify anything below this line                           */
/* **************************************************************** */

#ifndef BUILD_LIB
// Print tree
template <class T>
void BST<T>::printTree()
{
    if (!isEmpty())
    {
        printNodesInOrder(root);
        std::cout << std::endl;
    } else {
        std::cout << "Empty Tree" << std::endl;
    }
}

// Print tree using level order traversal
template <class T>
void BST<T>::printNodesInOrder(Node<T> * node)
{
    Node<T>*q[100];
    int head = 0;
    int tail = 0;
    q[0] = root;
    tail++;
    
    while (head != tail) {
        Node<T> *n = q[head];
        head++;
        std::cout << "Node " << n->data << " ";
        if (n->left != nullptr) {
            std::cout << " left child: " << n->left->data;
            q[tail] = n->left;
            tail++;
        }
        if (n->right != nullptr) {
            std::cout << " right child: " << n->right->data;
            q[tail] = n->right;
            tail++;
        }
        
        if (n->left == nullptr && n->right == nullptr) {
            std::cout << " no children";
        }
        std::cout << std::endl;
    }
}
#endif

template class BST<int>;
