/*
 * Course.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Jongwook Baik
 * Platform: Windows 10
 * Main IDE: Eclipse Neon 2.0
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include <iostream>
using namespace std;

class Course {
private:
	string crn;
	string courseName;
	string courseCode;
	string department;
	string professorName;

public:
	// Constructor
    Course();
	Course(string crn, string courseName, string courseCode, string department, string professorName);
	
    // Destructor
    ~Course() {}
    
    //Accessors
	string getCrn() const;
	string getCourseName() const;
	string getCourseCode() const;
	string getDepartment() const;
	string getProfessorName() const;
    
    //Mutators
	void setCrn(string crn);
	void setCourseName(string courseName);
	void setCourseCode(string courseCode);
	void setDepartment(string department);
	void setProfessorName(string professorName);
};

ostream &operator<<(ostream &strm, const Course &obj);

#endif /* COURSE_H_ */
