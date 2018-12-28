/*
 * Hash.h
 * <Team Project - Group 3>
 *
 * Programmer: Tu Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 *
 * The role of the Hash in our application is to have more efficiently in searching
 * and deleting data by the primary key (CRN) because the Big O notation is constant.
 */

#ifndef HASH_H_
#define HASH_H_

#include "HashElem.h"
#include <cmath>
using namespace std;

class Hash {
private:
	HashElem* arrElem;
	int loadFactor, collision, size, numElem;

public:
	//Construtors & destructor
	Hash();
	Hash(int s);
	~Hash();

	// Accessors
	int getSize() { return size; };
	int getLoadFactor() { return (numElem * 100) / size; };
	int getNumElem() { return numElem; };

	// Required functions
	int badHash(const string key);
	int goodHash(const string key);
	void displayConsole(void visit(Course &));
	void displayOutFile(ostream &out, void visit(ostream &, Course &));
	bool insert(Course*);
	bool remove(string, Course&);
	bool search(string, Course&);
	void statistic();

	//  Credit: JongWook Baek did this to traverse the hash for the using of re-hashing
	Course* traverse();
};

#endif
