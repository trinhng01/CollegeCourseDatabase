/*
* FileIO.h
* <Team Project - Group 3>
*
* Programmer: Jongwook Baik
* Platform: Windows 10
* Main IDE: Eclipse Neon 2.0
*
* Lecture: CIS 22C Winter 2017, De Anza College
* Instructor: Delia Garbacea
*/

#ifndef FILEIO_H_
#define FILEIO_H_

#include <fstream>
#include <string>
#include "Hash.h"
#include "Course.h"
#include "BinarySearchTree.h"

//Define a const file name.
#define inFileName "DACourse.txt"
#define outFileName "DACourseOutput.txt"

class FileIO{
private:
	string trim(string str);
	int countLines(string name);
	int nextPrime(int number);
	bool isPrime(int number);
	void openFileToRead(string name, ifstream& result);
	void openFileToWrite(string name, ofstream& result);
	Course* readCourse(ifstream& inputFile);

public:
	//read from file
	void readFromFile(BinarySearchTree<Course>* &treeUnique, BinarySearchTree<Course>* &treeSecondary, Hash* &hash);

	//save to file
	void saveToFile(BinarySearchTree<Course> *treeUnique, BinarySearchTree<Course> *treeSecondary, Hash *hash);

	void reHash(Hash *hash);
};

#endif /* FILEIO_H_ */
