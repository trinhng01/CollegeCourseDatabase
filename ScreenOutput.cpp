/*
* ScreenOutput.cpp
* <Team Project - Group 3>
*
* Programmer: Khoa Pham
* Platform: Windows 7
* Main IDE: Visual Studio 2015
*
* Lecture: CIS 22C Winter 2017, De Anza College
* Instructor: Delia Garbacea
*
*/

#include "ScreenOutput.h"

//Funtion Prototypes
void displayTree(Course&);
void displayTable(Course&);
void displayCourse(Course&);
void displayOneCourse(Course&);
void compareUnique(Course newNodePtr, Course nodePtr, int &result);
void compareSecondary(Course newNodePtr, Course nodePtr, int &result);

/************************************************************

 Programmer: Khoa Pham
 Function clearUno will clear all the stacks of the user by
 pop all the items in the stack( if any), so the user can't
 undo any delete one, unless they delete a new one.

***********************************************************/

bool ScreenOutput::clearStack(Stack<Course> &stack)
{
    Course noUseItem;
    if (stack.isEmpty())
    {
        cout << "\n**This is for the purpose of TESTING!\n"
        << "\n******************************\n"
        << "* No more Deleted Course(s) *\n"
        << "******************************";
        return true;
    }
    else{
        cout << "\n==================== CLEAN DELETED COURSES STACK ====================";
        cout << "\n\n**This is for the purpose of TESTING!\n\n";
    
        cout << "===> "<< stack.getCount() << " Delete Course(s) left for Undo Delete: " << endl;
        while (!stack.isEmpty())
        {
            stack.pop(noUseItem);
            displayOneCourse(noUseItem);
        }
        cout << "\n*********************************************************************\n"
             << "* Deleted Course(s) will be permanently removed out of the database *\n"
             << "*********************************************************************\n";
    }
    return true;
}

/************************************************************

 Programmer: Khoa Pham
 undoNode function will undo the node that is deleted
 in reverse order. It will print a warning if the stack
 doesn't have anything to undo.

***********************************************************/
bool ScreenOutput::undoDeleteCourse(BinarySearchTree<Course> *treeUnique,
	BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course> &stack, Course& temp)
{
	if (!stack.isEmpty())
	{
		Course* delItem = new Course;
		stack.pop(*delItem);
		temp = (*delItem);	//to know which course get undo
		treeUnique->insert(delItem, compareUnique);
		treeSecondary->insert(delItem, compareSecondary);
		hash->insert(delItem);
		return true;
	}
	else
		return false;
}


/************************************************************

 Programmer: Trinh Nguyen & Khoa Pham
 Purpose: This function will allow the user to view the
 database in different ways. It will display an menu of
 5 options below and execute according to input.

***********************************************************/

void ScreenOutput::DisplayManager(BinarySearchTree<Course> *treeUnique,
	BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
	Display display;
	string choice;
	do{
		cout <<
			"\n\t __________________________________________\n"
			"\t|                                          |\n"
			"\t|               DISPLAY MENU               |\n"
			"\t|------------------------------------------|\n"
			"\t| U. Diplay unsorted data                  |\n"
			"\t| P. Display sorted Course CRN data        |\n"
			"\t| S. Display sorted Course Name data       |\n"
			"\t| D. Special display, as an indented list  |\n"
			"\t| R. Return to Main Menu                   |\n"
			"\t|__________________________________________|\n";

		cout << "\nYour choice ==> ";
		getline(cin, choice);
		switch (toupper(choice[0]))
		{
		case 'U': // Diplay unsorted data using hash table
		{
					  cout << "\t\t\t\t\t\t\t~ "
						  "DISPLAY ALL COURSES IN UNSORTED ORDER ~\n";
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  display.displayHeader();
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  hash->displayConsole(displayTable);
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  break;
		}
		case 'P': // Display sorted Course CRN data using the unique-key tree
		{
					  cout << "\t\t\t\t\t\t\t~ "
						  "DISPLAY ALL COURSES IN SORTED CRN ORDER ~\n";
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  display.displayHeader();
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  treeUnique->inOrder(displayTable);
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  break;
		}
		case 'S': // Display sorted Course Name data using the secondary-key tree
		{
					  cout << "\t\t\t\t\t\t~ "
						  "DISPLAY ALL COURSES IN SORTED COURSE NAME ORDER ~\n";
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  display.displayHeader();
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  treeSecondary->inOrder(displayTable);
					  for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
					  cout << endl;
					  break;
		}
		case 'D':   // Special display, as an indented list
		{
						cout << "\t\t\t\t\t\t~ "
							"SPECIAL DISPLAY - DISPLAY ALL COURSES IN "
							"INDENTED LIST IN SORTED CRN ORDER ~\n\n";
						treeUnique->printTreeConsole(displayTree);
						break;
		}
		case 'R':
		{
					//Return to Main Menu
					break;
		}
			// User-Interface - Have user reenter until getting a valid entry
		default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
			break;
		}
	} while (toupper(choice[0]) != 'R');
	return;
}

/************************************************************
 
 Programmer: Trinh Nguyen & Khoa Pham
 Purpose: This function will allow the user to search for a
 Course in the database. It will display an menu of
 three options (search by CRN, Name, or return to main menu)
 and execute according to input. It then asks user to target
 to be search and then modify the info to its
 appropriate format. If FOUND, then display all the info,
 if NOT, then display a NOT FOUND message
 
 ***********************************************************/
void ScreenOutput::SearchManager(BinarySearchTree<Course> *treeUnique,
                                 BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    Display display;
    string temp;
    Course item, returnedItem;
    int count = 0;
    BinaryNode<Course>* returnedNode = treeSecondary->getRootPtr();
    string choice;
    do{
        cout <<
        "\n\t __________________________________\n"
        "\t|                                  |\n"
        "\t|            SEARCH MENU           |\n"
        "\t|----------------------------------|\n"
        "\t| P. Search Course CRN             |\n"
        "\t| S. Search Course Name            |\n"
        "\t| R. Return to Main Menu           |\n"
        "\t|__________________________________|\n";
        
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        switch (toupper(choice[0]))
        {
            case 'P':
            {
                cout << "Please enter the CRN of the course to search: ";
                temp = display.CRNInputValidation();
                item.setCourseName(temp);
                if (hash->search(temp, item))
                {
                    cout << "Course CRN " << temp << " is FOUND!" << endl;
                    displayCourse(item);
                }
                else
                    cout << "Course with CRN " << temp << " is NOT FOUND!" << endl;
                break;
            }
                
            case 'S':
            {
                cout << "Please enter the Course Name: ";
                temp = display.LineInputModify();
                item.setCourseName(temp);
                
                if (treeSecondary->getEntry(item, compareSecondary, &returnedNode))
                {
                    count = 1;
                    cout << "\nSEARCHING Course Name...\n";
                    item = *(returnedNode->getItem());
                    displayCourse(item);
                    
                    //search for other duplicates
                    returnedNode = returnedNode->getRightPtr();
                    while (treeSecondary->getEntry(item, compareSecondary, &returnedNode))
                    {
                        cout << "\n-----------------------------------------------\n";
                        item = *(returnedNode->getItem());
                        displayCourse(item);
                        returnedNode = returnedNode->getRightPtr();
                        count++;
                    }
                    cout << "\n===> FOUND " << count << " match(es).\n";
                }
                else
                {
                    cout << "Course with Name " << temp << " is NOT FOUND" << endl;
                }
                returnedNode = treeSecondary->getRootPtr();
                break;
            }
                
            case 'R':
            {
                //Return to Main Menu
                break;
            }
                
                // User-Interface - Have user reenter until getting a valid entry
            default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
                break;
        } // end switch
    } while (toupper(choice[0]) != 'R');
    return;
}
