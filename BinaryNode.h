/*
* BinaryNode.h
* <Team Project - Group 3>
*
* Programmer: Jyn Heng Yu
* Created by Frank M. Carrano and Tim Henry.
* Modified by: Jyh Heng Yu
* Platform: Windows 10
* Main IDE: Visual Studio 2015
*
* Lecture: CIS 22C Winter 2017, De Anza College
* Instructor: Delia Garbacea
*/

#ifndef _BINARY_NODE
#define _BINARY_NODE
#include <iomanip>

using namespace std;

template<class ItemType>
class BinaryNode
{
private:
	ItemType*             item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child
public:

	//Constructors
	BinaryNode(ItemType* anItem)	{ item = anItem; leftPtr = NULL; rightPtr = NULL; }
	BinaryNode(ItemType* anItem,
		BinaryNode<ItemType>* left,
		BinaryNode<ItemType>* right) {
		item = anItem; leftPtr = left; rightPtr = right;
	}
	BinaryNode() { item = NULL; leftPtr = NULL; rightPtr = NULL; }

	//Mutators
	void setItem(ItemType* anItem) { item = anItem; }
	void setLeftPtr(BinaryNode<ItemType>* left) { leftPtr = left; }
	void setRightPtr(BinaryNode<ItemType>* right) { rightPtr = right; }

	//Accessors
	ItemType* getItem() const	 { return item; }
	BinaryNode<ItemType>* getLeftPtr() const  { return leftPtr; }
	BinaryNode<ItemType>* getRightPtr() const { return rightPtr; }

	bool isLeaf() const
	{
		bool status = false;
		if (leftPtr == 0 && rightPtr == 0)
			return status = true;
		else
			return status;
	}
};

#endif 