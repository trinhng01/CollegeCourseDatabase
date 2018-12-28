/*
 * Course.h
 * <Team Project - Group 3>
 *
 * Programmer: Jongwook Baik
 * Platform: Windows 10
 * Main IDE: Eclipse Neon 2.0
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#include "Course.h"

// Programmer: Jongwook Baik
/*****************************************************
*               Overloaded Constructor               *
******************************************************/
Course::Course(string crn, string courseName, string courseCode, string department, string professorName) {
	this->crn = crn;
	this->courseName = courseName;
	this->courseCode = courseCode;
	this->department = department;
	this->professorName = professorName;
}

// Programmer: Jongwook Baik
/*****************************************************
*                 Default Constructor                *
******************************************************/
Course::Course() {
	this->crn = "";
	this->courseName = "";
	this->courseCode = "";
	this->department = "";
	this->professorName = "";
}

// Programmer: Jongwook Baik
/********************* Accessors *********************
* Member functions that allow access to data members *
******************************************************/

// Programmer: Jongwook Baik
// getCrn and returns crn
string Course::getCrn() const {
	return crn;
}

// Programmer: Jongwook Baik
// getCourseName gets the value of courseName and returns courseName
string Course::getCourseName() const {
	return courseName;
}

// Programmer: Jongwook Baik
// getCourseCode gets the value of courseCode and returns courseCode
string Course::getCourseCode() const {
	return courseCode;
}

// Programmer: Jongwook Baik
// getDepartment gets the value of department and returns department
string Course::getDepartment() const {
	return department;
}

// Programmer: Jongwook Baik
// getProfessorNamee gets the value of professorName and returns professorName
string Course::getProfessorName() const {
	return professorName;
}

// Programmer: Jongwook Baik
/********************** Mutators **********************
*   Member functions that allow for modification of  *
*   the data members                                 *
******************************************************/

// Programmer: Jongwook Baik
// setCrn sets the value of the member variable crn
void Course::setCrn(string crn) {
	this->crn = crn;
}

// Programmer: Jongwook Baik
// setCourseName sets the value of the member variable courseName
void Course::setCourseName(string courseName) {
	this->courseName = courseName;
}

// Programmer: Jongwook Baik
// setCourseCode sets the value of the member variable courseCode
void Course::setCourseCode(string courseCode) {
	this->courseCode = courseCode;
}

// Programmer: Jongwook Baik
// setDepartment sets the value of the member variable department
void Course::setDepartment(string department) {
	this->department = department;
}

// Programmer: Jongwook Baik
// setProfessorName sets the value of the member variable professorName
void Course::setProfessorName(string professorName) {
	this->professorName = professorName;
}

// Programmer: Jongwook Baik
/******************************************************
*           Class template for output stream         *
******************************************************/
ostream &operator<<(ostream &strm, const Course &obj)
{
	strm << obj.getCrn() << "\t\t"
		<< obj.getCourseName() << "\t\t"
		<< obj.getCourseCode() << "\t\t"
		<< obj.getDepartment() << "\t\t"
		<< obj.getProfessorName() << endl;
	return strm;
}
