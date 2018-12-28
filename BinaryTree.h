/*
* BinaryTree.h
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

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"
#include "Stack.h"

template<class ItemType>
class BinaryTree
{
	//Protected members: private variables that can be accessed by derived class.
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree
public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }

	// common functions for all binary trees
	bool isEmpty() const	{ return count == 0; }
	int size() const	    { return count; }
	void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void inOrder(void visit(ItemType & data)) const  { _inorder(visit, rootPtr); }
	BinaryNode<ItemType>* getRootPtr() { return rootPtr; }

	// abstract functions to be implemented by derived class
	virtual bool insert(ItemType* newEntry, void visit(ItemType dataL, ItemType dataR, int &result)) = 0;
	virtual bool remove(const ItemType & target, void visit(ItemType dataL, ItemType dataR, int &result)) = 0;
	virtual bool getEntry(const ItemType& anEntry, void visit(ItemType dataL, ItemType dataR, int &result), BinaryNode<ItemType>** returnedItem) = 0;

	// display tree as an intended list.
	void printTreeConsole(void visit(ItemType & data)) const
	{
		int level = 1;
		_printTreeConsole(visit, rootPtr, level);
	}

	// display tree as an intended list.
	void printTreeOutputFile(ostream &out, void visit(ostream &, ItemType &)) const
	{
		int level = 1;
		_printTreeOutputFile(out, visit, rootPtr, level);
	}
	//breadth traverse the tree.
	void breadthTraverse(void visit(ItemType & data)) const { _breadthTraversal(visit, rootPtr); }

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _printTreeConsole(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level) const;
	void _printTreeOutputFile(ostream &out, void visit(ostream &, ItemType &), BinaryNode<ItemType>* nodePtr, int level) const;
	void _breadthTraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
};

/////////////////////////////// Private Functions ///////////////////////////////////////////

//***************************************************************
// _breadthTraversal() is a private function accessed by
// breadthTraversal function to traverse the tree in breadth
// order. (using a private function to access the
// tree is to protect the integrity of the tree.)
//***************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_breadthTraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	BinaryNode<ItemType>* nodeTemp;
	BinaryNode<ItemType> *pWalk;
	Queue<BinaryNode<ItemType>*> store;
	ItemType itemTemp;
	pWalk = nodePtr;

	if (nodePtr == NULL)
		return;

	store.enqueue(pWalk);
	while (!store.isEmpty())
	{
		store.queueFront(pWalk);
		store.dequeue(nodeTemp);
		itemTemp = nodeTemp->getItem();
		visit(itemTemp);

		//check if there is left child.
		if (pWalk->getLeftPtr() != NULL)
			store.enqueue(pWalk->getLeftPtr());
		//check if there is right child.
		if (pWalk->getRightPtr() != NULL)
			store.enqueue(pWalk->getRightPtr());
	}
}
//****************************************************************************
// _printTreeConsole is a private function that is called by printTree function
// to print the binary search tree in a certain format onto the screen.
// (using a private function to access the tree is to protect the integrity
// of the tree.)
//****************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printTreeConsole(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level) const
{
	ItemType item = *nodePtr->getItem();
	int space = level;
	cout << setw((space - 1) * 10) << level << ".) ";
	visit(item);
	if (nodePtr->getRightPtr() != NULL)
		_printTreeConsole(visit, nodePtr->getRightPtr(), (level + 1));
	if (nodePtr->getLeftPtr() != NULL)
		_printTreeConsole(visit, nodePtr->getLeftPtr(), (level + 1));

	return;
}


//****************************************************************************
// _printTreeOutputFile is a private function that is called by printTree function
// to print the binary search tree in a certain format intoa a file.
// (using a private function to access the tree is to protect the integrity
// of the tree.)
//****************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printTreeOutputFile(ostream &out, void visit(ostream &, ItemType &), BinaryNode<ItemType>* nodePtr, int level) const
{
	ItemType item = *nodePtr->getItem();
	int space = level;
	out << setw((space - 1) * 10) << level << ".) ";
	visit(out, item);
	if (nodePtr->getRightPtr() != NULL)
		_printTreeOutputFile(out, visit, nodePtr->getRightPtr(), (level + 1));
	if (nodePtr->getLeftPtr() != NULL)
		_printTreeOutputFile(out, visit, nodePtr->getLeftPtr(), (level + 1));

	return;
}

//*************************************************************************
// _inorder() is a private function that is called by inorder
// function to traverse the tree by inorder. (using a private
// function to access the tree is to protect the integrity of the tree.)
//*************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType & data), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType *item = nodePtr->getItem();
		visit(*item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

#endif