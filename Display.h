/*
* Display.h
* <Team Project - Group 3>
*
* Programmer: Trinh Nguyen
* Platform: Mac OS 10 (Sierra)
* Main IDE: Xcode
*
* Lecture: CIS 22C Winter 2017, De Anza College
* Instructor: Delia Garbacea
*/

#ifndef Display_hpp
#define Display_hpp

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stack>
#include "Course.h"
#include "FileIO.h"
#include "Hash.h"
#include "ScreenOutput.h"
#include "BinarySearchTree.h" //BST ADT
using namespace std;
#define TABLE_LENGTH 156

class Display {
private:
	//Functions to perform main tasks
	void InsertManager(BinarySearchTree<Course>*, BinarySearchTree<Course>*, Hash*&);
	void DeleteManager(BinarySearchTree<Course>*, BinarySearchTree<Course>*, Hash*, Stack<Course>&);
	void UndoDeleteManager(BinarySearchTree<Course>*, BinarySearchTree<Course>*, Hash*, Stack<Course>&);
	void DisplayStatistics(Hash*);
	void SaveToFile(FileIO, BinarySearchTree<Course>*, BinarySearchTree<Course>*, Hash*);

    void DeleteCoreCode(string temp, BinarySearchTree<Course> *treeUnique, BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course>& stack);
    bool searchTreeSeondary(Queue<string> & CRNTemp, BinarySearchTree<Course> *treeSecondary, Course item, int & count, string temp);
public:
	//Display Functions
	void displayHeader();
	void displayMenu();

	//Input Validation and Modification
	string CRNInputValidation();
	string LineInputModify();
	string CourseCodeInputModify();

	//Display Project Info
	void printProjectIntro();

	//Main Interaction with data and user
	void ProcessMenu(BinarySearchTree<Course>*, BinarySearchTree<Course>*, Hash*);
};

#endif /* Display_hpp */
