/*
 * BinarySearchTree.h
 * <Team Project - Group 3>
 *
 * Programmer: Jyh Heng Yu
 * Created by Frank M. Carrano and Tim Henry.
 * Modified by: Jyh Heng Yu
 * Platform: Windows 7
 * Main IDE: Visual Studio 2013
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <iomanip>
#include <iostream>
using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // insert a new entry to the binary search tree.
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, void visit(ItemType dataL, ItemType dataR, int &result));
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success, void visit(ItemType dataL, ItemType dataR, int &result));
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* nodePtr, const ItemType & target, void visit(ItemType dataL, ItemType dataR, int &result)) const;
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType** successor);
    
public:
    // insert a node at the correct location.
    bool insert(ItemType* newEntry, void visit(ItemType dataL, ItemType dataR, int &result));
    // remove a node if found
    bool remove(const ItemType & target, void visit(ItemType dataL, ItemType dataR, int &result));
    // find a target node
    bool getEntry(const ItemType& anEntry, void visit(ItemType dataL, ItemType dataR, int &result), BinaryNode<ItemType>** returnedItem);
};

///////////////////////// public function definitions ///////////////////////////

//*************************************************************************
// insert function is a public function that inserts new node by
// using _insert function in private member.(using a private
// function to access the tree is to protect the integrity of the tree.
//*************************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType* newEntry, void visit(ItemType dataL, ItemType dataR, int &result))
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, visit);
    return true;
}

//***************************************************************************
// remove function is to locate the entry from user and delete it. This is
// only the public function called in main. Detailed execution will be
// done in _remove private function.
//***************************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target, void visit(ItemType dataL, ItemType dataR, int &result))
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful, visit);
    return isSuccessful;
}

//************************************************************************
// getEntry is a public function that searches a target student by
// using a private member function called findNode. (using a private
// function to access the tree is to protect the integrity of the tree.
//************************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, void visit(ItemType dataL, ItemType dataR, int &result), BinaryNode<ItemType>** returnedItem)//deleted into non-constant function, changed returned item into double pointer
{
    bool found = false;
    BinaryNode<ItemType>* temp;
    
    temp = findNode(*returnedItem, anEntry, visit);
    if (temp != NULL)
    {
        *returnedItem = temp;
        found = true;
        return found;
    }
    else
        return found;
}


//////////////////////////// private functions ////////////////////////////////////////////

//*******************************************************************************
// findNode() function is a private function that is called by getEntry function
// to look for a student entered by the user.(using a private
// function to access the tree is to protect the integrity of the tree.)
//*******************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr, const ItemType & target,
                                                           void visit(ItemType dataL, ItemType dataR, int &result)) const
{
    BinaryNode<ItemType>* pWalk;
    ItemType compareTemp;
    pWalk = nodePtr;
    int compare = 0;
    
    while (pWalk != NULL)
    {
        compareTemp = *(pWalk->getItem());
        visit(target, compareTemp, compare);
        //compare = 1 --> newnodePtr < nodePtr
        //compare = 2 --> newNodePtr > nodePtr
        //compare = 3 --> newNodePtr = nodePtr
        //compare = 4 --> duplicates
        if (compare == 1)
            pWalk = pWalk->getLeftPtr();
        else if (compare == 2)
            pWalk = pWalk->getRightPtr();
        else
            return pWalk;
    }
    return pWalk;
}

//*******************************************************************************
// _insert() function is a private function that is called by insert function
// to insert a new entry to the binary search tree.(using a private
// function to access the tree is to protect the integrity of the tree.)
//*******************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr,
                                                          void visit(ItemType dataL, ItemType dataR, int &result))
{
    int compare;
    BinaryNode<ItemType>* tempPtr;
    if (nodePtr == NULL)
    {
        return newNodePtr;
    }
    else
    {
        visit(*(newNodePtr->getItem()), *(nodePtr->getItem()), compare);
        //compare = 1 --> newnodePtr < nodePtr
        //compare = 2 --> newNodePtr > nodePtr
        //compare = 3 --> newNodePtr = nodePtr
        //compare = 4 --> duplicates
        if (compare == 1)
        {
            tempPtr = _insert(nodePtr->getLeftPtr(), newNodePtr, visit);
            nodePtr->setLeftPtr(tempPtr);
        }
        else
        {
            //set to right node if it is greater of equal to the node item.
            tempPtr = _insert(nodePtr->getRightPtr(), newNodePtr, visit);
            nodePtr->setRightPtr(tempPtr);
        }
    }
    this->count++;
    return nodePtr;
}


//***********************************************************************
// _remove private function is the function to remove a targeted item
// entered the user. (private function for tree's integrity)
//***********************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success,
                                                          void visit(ItemType dataL, ItemType dataR, int &result))
{
    int compare;
    //to check if this is a leaf, return NULL after search to the end of the tree
    if (nodePtr == NULL)
    {
        success = false;
        return NULL;
    }
    visit(target, *(nodePtr->getItem()), compare);
    
    //compare = 1 --> newnodePtr < nodePtr
    //comapre = 2 --> newNodePtr > nodePtr
    //compare = 3 --> newNodePtr = nodePtr
    //compare = 4 --> duplicates
    if (compare == 1)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, visit));
    else if (compare == 2)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, visit));
    else if (compare == 3)
    {
        //node found (nodePtr is the one)
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    //when duplicate, search right node for exact node
    else
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, visit));
    return nodePtr;
}

//*************************************************************
// deleteNode private function is a function that deletes a
// certain node given by the user.
//**************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    //check if this node is at the end of the tree.
    if (nodePtr->isLeaf())
    {
        //delete node directly.
        delete nodePtr;
        //set nodePtr to NULL
        nodePtr = NULL;
        return nodePtr;
    }
    //check if this node has any left node
    else if (nodePtr->getLeftPtr() == NULL)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = NULL;
        return nodeToConnectPtr;
    }
    //check if this node has any right node
    else if (nodePtr->getRightPtr() == NULL)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = NULL;
        //change the original nodePtr to nodeToConnectPtr.
        return nodeToConnectPtr;
    }
    //if there are two leaves for this node
    else
    {
        //newNodeValue is for the value that we are suppose to link.
        ItemType* newNodeValue = NULL;
        //setting the rightnode of nodePtr as largest of it's right tree(right tree left most value.)
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), &newNodeValue));
        //setting the new item into the deleted node
        nodePtr->setItem(newNodeValue);
        //return newly modified node.
        return nodePtr;
    }
}

//***************************************************************************
// removeLeftMost function is called in deleteNode function, and is 
// programmed to find the smallest node located at the right sub tree.
//***************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType** successor)
{
    if (nodePtr->getLeftPtr() == NULL)
    {
        *(successor) = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}

#endif
