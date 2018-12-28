/*
 * HashElem.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Tu Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */


#include "Course.h"
#include "HashElem.h"
#include <iostream>

using namespace std;

// Constructor
HashElem::HashElem() {
	this->item = 0;
	flag = 0;
}

HashElem::HashElem(Course* item) {
	this->item = item;
	flag = 0;
}
void HashElem::setItem(Course * c) {
	item = c;
}
// this function is to set every members of the Course to Null
// since the remove function of the hash can't change the size
// by remove completly the element. 
void HashElem::setItemToNull() {
	(*item).setCrn("");
	(*item).setCourseName("");
	(*item).setCourseCode("");
	(*item).setDepartment("");
	(*item).setProfessorName("");
}

ostream &operator<<(ostream &strm, HashElem& obj){
	strm << obj.getItem();
	return strm;
}
