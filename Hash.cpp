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
*/

#include "Hash.h"

//Public function
Hash::Hash() {
	size = 0;
	arrElem = 0;
	loadFactor = 0;
	collision = 0;
	numElem = 0;
}
Hash::Hash(int s) {
	size = s;
	arrElem = new HashElem[size];
	loadFactor = 0;
	collision = 0;
	numElem = 0;
}

// Display() prints the elements in the Course to console
void Hash::displayConsole(void visit(Course &)) {
	for (int i = 0; i < size; i++) {
		if (arrElem[i].getFlag() == 1) {
			visit(*arrElem[i].getItem());
		}
	}
}

// Display() prints the elements in the Course to text file
void Hash::displayOutFile(ostream &out, void visit(ostream &, Course &)) {
	for (int i = 0; i < size; i++) {
		if (arrElem[i].getFlag() == 1) {
			visit(out, *arrElem[i].getItem());
		}
	}
}
// badHash function is to create the address for the Course obj based
// on their unique key (expecting a lot collisions)
int Hash::badHash(const string key) {
	int index = 0;
	for (unsigned int i = 0; i < key.length(); i++) {
		index += (int)key[i];   // the sum of itself
	}
	return index%size;
}

// goodHash function is to create the address for the Course obj based
// on their unique key (expecting less collisions)
int Hash::goodHash(const string key) {
	int index = 0;
	for (unsigned int i = 0; i < key.length(); i++) {
		index += pow((int)key[i], 3);  // the sum of its square
	}
	return index%size;
}

//insert() adds Course object to the hash by hashing the primary key
bool Hash::insert(Course *obj) {
	bool isInsert = false;
	int index = goodHash(obj->getCrn());
	//int index = badHash(obj->getCrn());

	do {
		if (arrElem[index].getFlag() == 1) {
			collision++;   // this collision variable is for the general hash Table
			arrElem[index].setCollisionEachItem(); // this collision is for individual item
		}
		if (arrElem[index].getFlag() != 1) {     // either empty or been removed
			arrElem[index].setItem(obj);
			arrElem[index].setFlag(1);
			numElem++;
			isInsert = true;
		}
		else {  // if it is not empty
			if (arrElem[index].getCollisionEachItem() % 2 == 0)
				//index = (index + 1) % size;
				index++;
			else
				//index = (index - 1 + size) % size;
				index--;
		}
	} while (!isInsert);
	return isInsert;
}

// remove function is to delete the data at given target
// by hashing the target and search for its location
bool Hash::remove(string target, Course& delItem) {
	int index = goodHash(target);
	//int index = badHash(target);
	int temp1 = index;
	int temp2 = index;
	Course tempC;
	if (arrElem[index].getFlag() == 0)
		return false;
	else {
		tempC = *(arrElem[index].getItem());
		if (tempC.getCrn() == target) {		 // if the target is found
			arrElem[index].setFlag(-1);
			delItem = tempC;
			arrElem[index].setItemToNull();
			numElem--;
			return true;
		}
	}
	Course tempC1, tempC2;
	while (arrElem[temp1].getFlag() != 0) {
		tempC1 = *(arrElem[temp1].getItem());
		if (tempC1.getCrn() != target)
			temp1++;
		else {
			arrElem[temp1].setFlag(-1);
			delItem = tempC1;
			arrElem[temp1].setItemToNull();
			numElem--;
			return true;
		}
	}
	while (arrElem[temp2].getFlag() != 0) {
		tempC2 = *(arrElem[temp2].getItem());
		if (tempC2.getCrn() != target)
			temp2--;
		else {
			arrElem[temp2].setFlag(-1);
			delItem = tempC2;
			arrElem[temp2].setItemToNull();
			numElem--;
			return true;
		}
	}
	return false;

}

// Searching the data by hasing the given string target
// then search for the location.
bool Hash::search(string target, Course& foundItem) {
	int index = goodHash(target);
	//int index = badHash(target);
	int temp1 = index;
	int temp2 = index;
	Course tempC, tempC1, tempC2;
	if (arrElem[index].getFlag() == 0)
		return false;
	else {
		tempC = *(arrElem[index].getItem());
		if (tempC.getCrn() == target) {  // if the target is found
			foundItem = tempC;
			return true;
		}
	}
	while (arrElem[temp1].getFlag() != 0) {
		tempC1 = *(arrElem[temp1].getItem());
		if (tempC1.getCrn() != target)
			temp1++;
		else {
			foundItem = tempC1;
			return true;
		}
	}
	while (arrElem[temp2].getFlag() != 0) {
		tempC2 = *(arrElem[temp2].getItem());
		if (tempC2.getCrn() != target)
			temp2--;
		else {
			foundItem = tempC2;
			return true;
		}
	}
	return false;
}

// Statistic function is to report the data about loadfactor
// and number of collision
void Hash::statistic() {
	loadFactor = (numElem * 100) / size;
	cout << left
		<< "\t| Table size: " << setw(22) << size << "|" << endl
		<< "\t| Load Factor: " << loadFactor << "%" << setw(19) << right << "|" << endl
		<< "\t| Total element: " << setw(19) << left << numElem << "|" << endl
		<< "\t| Total collision: " << setw(17) << collision << "|" << endl << "\t|";
	for (int i = 0; i < 35; i++) cout << "_";
	cout << "|\n";
}

// Credit: JongWook Baek did this to traverse the hash for the using of re-hashing
Course* Hash::traverse() {
	Course* result = new Course[numElem];
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (arrElem[i].getFlag() == 1) {
			result[count] = *arrElem[i].getItem();
			count++;
		}
	}
	return result;
}

//Destructor
Hash::~Hash() {
	delete[] arrElem;
}

