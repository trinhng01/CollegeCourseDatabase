/*
 ______________________________________                 ___________________________________________________
|                                      |               |                                                   |
|           CIS 22C-02Y                |               |   Unit 1: Team Coordinator - Trinh Nguyen         |
|         M/W 1:30 - 3:20              |               |   Unit 2: BST Algorithms - Jyn Heng Yu (Henry)    |
|     Professor Delia Gârbacea         |               |   Unit 3: Hash List Algorithms - Tu Nguyen        |
|         March 24, 2017               |               |   Unit 4: Screen Output - Khoa Pham               |
|______________________________________|               |   Unit 5: File I/O - JongWook Baek (Tony)         |
|                                      |               |___________________________________________________|
|       TEAM 3 - WINTER 2016           |               |                                                   |
|     DE ANZA COURSE DATABASE          |               |     ~ WELCOME TO THE NEW COURSES SYSTEM OF ~      |
|  IDE: Visual Studio, Xcode & Eclipse |               |               ~ DE ANZA COLLEGE ~                 |
|______________________________________|               |___________________________________________________|
*/

/*
* Main.cpp
* <Team Project - Group 3>
*
* Programmer: Trinh Nguyen
* Platform: Mac OS 10 (Sierra)
* Main IDE: Xcode
*
*/

#include "Course.h"
#include "FileIO.h"
#include "Display.h"
#include "ScreenOutPut.h"
#include "Hash.h"
#include "BinarySearchTree.h"
using namespace std;

//Define a const input file name
#define fileName "DACourse.txt"
#define outFileName "DACourseOutput.txt"

int main(void)
{
	BinarySearchTree<Course> *treeUnique = new BinarySearchTree<Course>;
	BinarySearchTree<Course> *treeSecondary = new BinarySearchTree<Course>;
	Hash *hash = new Hash;

	Display driver;
	driver.ProcessMenu(treeUnique, treeSecondary, hash);
	return 0;
}

