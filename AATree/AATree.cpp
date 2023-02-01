//
//  AATree.cpp
//

#include "AATree.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
template <class T>
AATree<T>::AATree()
{
    // TODO: Create sentinel node (i.e. bottomNode)
    // assign the sentinel node to root, lastNode, and deletedNode
    bottomNode = new Node<T>(-1);
    bottomNode -> level = 0;
    bottomNode -> left = bottomNode -> right = root = lastNode = deletedNode = bottomNode;
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
template <class T>
AATree<T>::~AATree()
{
    // TODO: Remove any nodes
    // don't forget to deallocate bottomNode
    makeEmpty();

    delete bottomNode;
}
#endif

/* **************************************************************** */

#if ISEMPTY || ALL
// TODO: isEmpty() method
template <class T>
bool AATree<T>::isEmpty()
{
    return root == bottomNode;
}
#endif

/* **************************************************************** */

#if FIND || ALL
// TODO: find() method
template <class T>
bool AATree<T>::find(const T &x)
{
    return findNode(root, x) != bottomNode;
}
#endif

/* **************************************************************** */

#if FINDNODE || ALL
// TODO: findNode() private method - iterative
template <class T>
Node<T> *AATree<T>::findNode(Node<T> *node, const T &x)
{
    while (node != bottomNode && node -> data != x)
    {
        x < node -> data ? node = node -> left : node = node -> right;
    }

    return node;
}
#endif

/* **************************************************************** */

#if FINDMIN || ALL
// TODO: findMin() method
template <class T>
const T &AATree<T>::findMin()
{
    return findMinNode(root) -> data;
}
#endif

/* **************************************************************** */

#if FINDMINNODE || ALL
// TODO: findMinNode() private method
template <class T>
Node<T> *AATree<T>::findMinNode(Node<T> *node)
{
    while (node -> left != bottomNode)
    {
        node = node -> left;
    }

    return node;
}
#endif

/* **************************************************************** */

#if FINDMAX || ALL
// TODO: findMax() method
template <class T>
const T &AATree<T>::findMax()
{
    return findMaxNode(root) -> data;
}
#endif

/* **************************************************************** */

#if FINDMAXNODE || ALL
// TODO: findMaxNode() private method
template <class T>
Node<T> *AATree<T>::findMaxNode(Node<T> *node)
{
    while (node -> right != bottomNode)
    {
        node = node -> right;
    }

    return node;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
// TODO: insert() method
template <class T>
void AATree<T>::insert(const T &x)
{
    insertNode(root, x);
}
#endif

/* **************************************************************** */

#if INSERTNODE || ALL
// TODO: insertNode() private method
template <class T>
void AATree<T>::insertNode(Node<T> *&node, const T &x)
{
    if (node == bottomNode)
    {
        node = new Node<T>(x, bottomNode, bottomNode, 1);
    }

    else
    {
        if (x < node -> data)
        {
            insertNode(node -> left, x);
        }

        else if (x > node -> data)
        {
            insertNode(node -> right, x);
        }
    }

    skew(node);

    split(node);
}
#endif

/* **************************************************************** */

#if REMOVE || ALL
// TODO: remove() method
template <class T>
void AATree<T>::remove(const T &x)
{
    removeNode(root, x);
}
#endif

/* **************************************************************** */

#if REMOVENODE || ALL
// TODO: removeNode() private method
template <class T>
void AATree<T>::removeNode(Node<T> *&node, const T &x)
{
    if (node != bottomNode)
    {
        lastNode = node;

        if (x < node -> data)
        {
            removeNode(node -> left, x);
        }

        else
        {
            deletedNode = node;

            removeNode(node -> right, x);
        }

        if (node == lastNode && deletedNode != bottomNode && x == deletedNode -> data)
        {
            deletedNode -> data = node -> data;
            deletedNode = bottomNode;

            node = node -> right;

            delete lastNode;
        }

        else if (node -> left -> level < node -> level - 1 || node -> right -> level < node -> level - 1)
        {
            node -> level = node -> level - 1;

            if (node -> right -> level > node -> level)
            {
                node -> right -> level = node -> level;
            }

            skew(node);
            skew(node -> right);
            skew(node -> right -> right);

            split(node);
            split(node -> right);
        }
    }
}
#endif

/* **************************************************************** */

#if SKEW || ALL
// TODO: skew() private method
template <class T>
void AATree<T>::skew(Node<T> *&node)
{
    if (node -> left -> level == node -> level)
    {
        Node<T> *tempNode = node;

        node = node -> left;

        tempNode -> left = node -> right;

        node -> right = tempNode;
    }
}
#endif

/* **************************************************************** */

#if SPLIT || ALL
// TODO: split() private method
template <class T>
void AATree<T>::split(Node<T> *&node)
{
    if (node -> right -> right -> level == node -> level)
    {
        Node<T> *tempNode = node;

        node = node -> right;

        tempNode -> right = node -> left;

        node -> left = tempNode;
        node -> level = node -> level + 1;
    }
}
#endif

/* **************************************************************** */

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
template <class T>
void AATree<T>::makeEmpty()
{
    removeAllNodes(root);

    root = bottomNode;
}
#endif

/* **************************************************************** */

#if REMOVEALLNODES || ALL
// TODO: removeAllNodes() private method
template <class T>
void AATree<T>::removeAllNodes(Node<T> *node)
{
    if ( node -> left != bottomNode)
    {
        removeAllNodes(node -> left);
    }

    if ( node -> right != bottomNode)
    {
        removeAllNodes(node -> right);
    }

    if (node != bottomNode)
    {
        delete node;
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
void AATree<T>::printTree(){
    if (root != bottomNode)
    {
        printNodesInOrder(root);
        std::cout << std::endl;
    } else {
        std::cout << "Empty Tree" << std::endl;
        std::cout << std::endl;
    }
}

// Print tree using level order traversal
template <class T>
void AATree<T>::printNodesInOrder(Node<T> * node)
{
    Node<T>* q[100];
    int head = 0;
    int tail = 0;
    q[0] = node;
    tail++;
    
    while (head != tail)
    {
        Node<T> *n = q[head];
        head++;
        std::cout << "Node " << n->data << " at level " << n->level << std::endl;
        if (n->left != bottomNode)
        {
            std::cout << "  " << n->data << " left child: " << n->left->data << std::endl;
            q[tail] = n->left;
            tail++;
        }
        if (n->right != bottomNode)
        {
            std::cout << "  " << n->data << " right child: " << n->right->data << std::endl;
            q[tail] = n->right;
            tail++;
        }
    }
}
#endif

template class AATree<int>;
