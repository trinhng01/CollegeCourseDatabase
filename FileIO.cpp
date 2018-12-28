/*
* FileIO.cpp
* <Team Project - Group 3>
*
* Programmer: Jongwook Baik
* Platform: Windows 10
* Main IDE: Eclipse Neon 2.0
*
* Lecture: CIS 22C Winter 2017, De Anza College
* Instructor: Delia Garbacea
*/

#include "FileIO.h"

// Function Prototypes
void displayCourse(ostream &out, Course &anItem);
void compareUnique(Course newNodePtr, Course nodePtr, int &result);
void compareSecondary(Course newNodePtr, Course nodePtr, int &result);

/******************* readFromFile ***********************
* Programmer: Jongwook Baik                             *
* Determine Hash size by counting the lines             *
* in the input file and multiplying it by 2, and choose *
* the next prime number. Read data from the input and   *
* insert them into the Hash Table and the two BSTs.     *
********************************************************/
void FileIO::readFromFile(BinarySearchTree<Course>* &treeUnique, BinarySearchTree<Course>* &treeSecondary, Hash* &hash) {

	int linesCount = countLines(inFileName);
	int hashSize = nextPrime(linesCount * 2);
	hash = new Hash(hashSize);

	ifstream inputFile;
	openFileToRead(inFileName, inputFile);
	while (inputFile.good()) {
		Course* course = readCourse(inputFile);
		if (course->getCrn() != "") {

			// Inserting to the two BSTs.
			treeUnique->insert(course, compareUnique);
			treeSecondary->insert(course, compareSecondary);

			// Inserting to the Hash Table.
			hash->insert(course);
			if (hash->getLoadFactor() >= 75) {
				reHash(hash);
			}
		}
		else
			delete course;
	}
	inputFile.close();

	return;
}

/********************* saveToFile ***********************
* Programmer: Jongwook Baik                             *
*              Print outputs to the file.               *
********************************************************/
void FileIO::saveToFile(BinarySearchTree<Course> *treeUnique, BinarySearchTree<Course> *treeSecondary, Hash *hash) {

	ofstream outputFile;
	openFileToWrite(outFileName, outputFile);

	outputFile << "\n\t\t\t\t\t\t\t\t\t\t*************************** UNIQUE BST ***************************" << endl;
	treeUnique->printTreeOutputFile(outputFile, displayCourse);

	outputFile << "\n\t\t\t\t\t\t\t\t\t\t************************* SECONDARY BST **************************" << endl;
	treeSecondary->printTreeOutputFile(outputFile, displayCourse);

	outputFile << "\n\t\t\t\t\t****************************** HASH TABLE ******************************" << endl;
	hash->displayOutFile(outputFile, displayCourse);

	//When the user selects “Save to file”, the undo stack is cleaned out
	//CLEAN STACK
	outputFile.close();
}

/******************* displayCourse **********************
* Programmer: Jongwook Baik                             *
*        Display function display an object.            *
********************************************************/
void displayCourse(ostream &out, Course &anItem){

	out << anItem;

	return;
}

/******************* compareUnique **********************
* Programmer: Jyn Heng Yu                               *
*    If new entry is smaller than original, return 1.   *
*    If larger, return 2. Anything else, return 3.      *
*    (Unique key is CRN.)                               *
********************************************************/

void compareUnique(Course newNodePtr, Course nodePtr, int &result) {

	/* result = 1 --> newnodePtr < nodePtr
	* result = 2 --> newNodePtr > nodePtr
	* result = 3 --> newNodePtr = nodePtr
	*/

	if (newNodePtr.getCrn() < nodePtr.getCrn())
		result = 1;
	else if (newNodePtr.getCrn() > nodePtr.getCrn())
		result = 2;
	else
		result = 3;

	return;
}

/****************** compareSecondary ********************
* Programmer: Jyn Heng Yu                               *
*   If new entry is smaller than original, return 1.    *
*   If larger, return 2. Anything else, return 3.       *
*   (Secondary key is class name.)                      *
********************************************************/

void compareSecondary(Course newNodePtr, Course nodePtr, int &result) {
    
    /* result = 1 --> newnodePtr < nodePtr
     * result = 2 --> newNodePtr > nodePtr
     * result = 3 --> newNodePtr = nodePtr
     * result = 4 --> duplicates (go search right node)
     */
    
    if (newNodePtr.getCourseName() < nodePtr.getCourseName())
        result = 1;
    else if (newNodePtr.getCourseName() > nodePtr.getCourseName())
        result = 2;
    else if (newNodePtr.getCourseName() == nodePtr.getCourseName())
    {
        if (newNodePtr.getCrn() == nodePtr.getCrn())
            result = 3;
        else
            result = 4;
    }
}

/*********************** reHash *************************
* Programmer: Jongwook Baik                             *
* When the load factor is 75, allocate another hash     *
* table (2 * actual size, and choose the next prime     *
* number), then traverse the hash table and hash each   *
* item into the new table using the same hash function  *
* and collision resolution method, and delete the old   *
* hash table.                                           *
********************************************************/
void FileIO::reHash(Hash *hash) {

	Hash* newHash = new Hash(nextPrime(hash->getSize() * 2));

	Course* hashElements = hash->traverse();
	for (int i = 0; i < hash->getNumElem(); i++) {
		newHash->insert(&hashElements[i]);
	}

	delete hash;
	hash = newHash;
}

/******************** readCourse ***********************
* Programmer: Jongwook Baik                            *
*             Read course line from file.              *
*******************************************************/
Course* FileIO::readCourse(ifstream& inputfile) {

	Course* result = new Course();
	string tempStr;

	getline(inputfile, tempStr, ';');
	result->setCrn(trim(tempStr));

	getline(inputfile, tempStr, ';');
	result->setCourseName(trim(tempStr));

	getline(inputfile, tempStr, ';');
	result->setCourseCode(trim(tempStr));

	getline(inputfile, tempStr, ';');
	result->setDepartment(trim(tempStr));

	getline(inputfile, tempStr, ';');
	result->setProfessorName(trim(tempStr));
	inputfile.ignore(256, '\n');

	return result;
}

/****** trim ******/
string FileIO::trim(string str) {
	return str.erase(0, str.find_first_not_of(" \t"));
}

/******************* openFileToRead *********************
* Programmer: Jongwook Baik                             *
*      If fail to open file, display an error message.  *
********************************************************/
void FileIO::openFileToRead(string name, ifstream& result){

	result.open(name);
	if (!result.good()) {
		cout << "Error opening file" << endl;
		exit(-1);
	}
}

/******************* openFileToWrite ********************
* Programmer: Jongwook Baik                             *
*      If fail to open file, display an error message.  *
********************************************************/
void FileIO::openFileToWrite(string name, ofstream& result) {

	result.open(name);
	if (!result.good()) {
		cout << "Error opening file" << endl;
		exit(-1);
	}
}

/********************* countLines ***********************
* Programmer: Jongwook Baik                             *
*           Calculate count of lines in file.           *
********************************************************/
int FileIO::countLines(string name) {

	ifstream file;
	openFileToRead(name, file);

	int result = 0;
	string tempStr;

	while (file.good()) {
		getline(file, tempStr);
		result++;
	}
	file.close();
	return result;
}

/********************* nextPrime ************************
* Programmer: Jongwook Baik                             *
*           Find first greater prime number.            *
********************************************************/
int FileIO::nextPrime(int number) {

	int result = number;
	while (!isPrime(result)){
		result++;
	}
	return result;
}

/********************* isPrime **************************
* Programmer: Jongwook Baik                             *
*             Check if number is prime.                 *
********************************************************/
bool FileIO::isPrime(int number){

	// Check for divisors less than sqrt(number).
	for (int i = 2; i * i <= number; i++) {
		// Found divisor.
		if (number % i == 0) {
			return false;
		}
	}

	// No divisors.
	return true;
}
