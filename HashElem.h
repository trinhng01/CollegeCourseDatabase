/*
 * HashElem.h
 * <Team Project - Group 3>
 *
 * Programmer: Tu Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */


#ifndef HASHELEM_H
#define HASHELEM_H

#include "Course.h"
#include <iomanip>

using namespace std;

class HashElem;

ostream &operator << (ostream &, const HashElem &);

class HashElem {
private:
	Course* item;
	int collisionEachItem;
	int flag;

public:
	//Constructor
	HashElem();
	HashElem(Course * item);

	//Accessors
	Course* getItem() { return item; };
	int getCollisionEachItem() { return collisionEachItem; };
	int getFlag() { return flag; };

	//Mutators
	void setItem(Course *);
	void setItemToNull ();
	void setCollisionEachItem() { collisionEachItem++; };
	void setFlag(int f) { flag = f; };

	//Operators
	friend ostream &operator << (ostream &, const HashElem &);
};
 
#endif 


