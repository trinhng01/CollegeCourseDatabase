/*
 * Display.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Trinh Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Xcode
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#include "Display.h"

//Funtion Prototypes
void displayTree(Course&);
void displayTable(Course&);
void displayOneCourse(Course&);
void reHash(Hash *hash);
void compareUnique(Course newNodePtr, Course nodePtr, int &result);
void compareSecondary(Course newNodePtr, Course nodePtr, int &result);

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display the introduction info
 (class info, professor, date submitted, team and member info,
 project info)
 
 ***********************************************************/

void Display::printProjectIntro()
{
    cout <<
    "\t _______________________________________                 ___________________________________________________\n"
    "\t|                                       |               |                                                   |\n"
    "\t|              CIS 22C-02Y              |               |   Unit 1: Team Coordinator - Trinh Nguyen         |\n"
    "\t|            M/W 1:30 - 3:20            |               |   Unit 2: BST Algorithms - Jyn Heng Yu (Henry)    |\n"
    "\t|        Professor Delia Garbacea       |               |   Unit 3: Hash List Algorithms - Tu Nguyen        |\n"
    "\t|           March 20th, 2017            |               |   Unit 4: Screen Output - Khoa Pham               |\n"
    "\t|_______________________________________|               |   Unit 5: File I/O - Jongwook Baik (Tony)         |\n"
    "\t|                                       |               |___________________________________________________|\n"
    "\t|         TEAM 3 - WINTER 2016          |               |                                                   |\n"
    "\t|       DE ANZA COURSE DATABASE         |               |     ~ WELCOME TO THE NEW COURSES SYSTEM OF ~      |\n"
    "\t|  IDE: Visual Studio, Xcode & Eclipse  |               |               ~ DE ANZA COLLEGE ~                 |\n"
    "\t|_______________________________________|               |___________________________________________________|\n";
    
    return;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function show the contents of the main menu
 
 ***********************************************************/

void Display::displayMenu()
{
    cout <<
    "\n\t __________________________________\n"
    "\t|                                  |\n"
    "\t|            MAIN MENU             |\n"
    "\t|----------------------------------|\n"
    "\t| A. Add a Course                  |\n"
    "\t| S. Search a Course               |\n"
    "\t| D. Remove a Course               |\n"
    "\t| L. Display Database              |\n"
    "\t| W. Write data to a file          |\n"
    "\t| M. Show Statistics               |\n"
    "\t| Q. Exit and Save to file         |\n"
    "\t|__________________________________|\n";
    
    return;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function displays the menu of the program and
 execute the program according to user input
 
 ***********************************************************/

void Display::ProcessMenu(BinarySearchTree<Course> *treeUnique,
                          BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    FileIO IO;
    IO.readFromFile(treeUnique, treeSecondary, hash);
    printProjectIntro();
    Stack<Course> stack;
    ScreenOutput op;
    string choice;
    do {
        displayMenu();
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        switch (toupper(choice[0]))
        {
            case 'A':   // ADD A COURSE
            {
                InsertManager(treeUnique, treeSecondary, hash);
                break;
            }
            case 'S':   // SEARCH A COURSE
            {
                op.SearchManager(treeUnique, treeSecondary, hash);
                break;
            }
            case 'D':   // DELETE A COURSE
            {
                DeleteManager(treeUnique, treeSecondary, hash, stack);
                break;
            }
            case 'L':   // DISPLAY DATABASE
            {
                op.DisplayManager(treeUnique, treeSecondary, hash);
                break;
            }
            case 'W':   // WRITE DATA TO FILE AND CLEAR STACK
            {
                op.clearStack(stack);
                SaveToFile(IO, treeUnique, treeSecondary, hash);
                break;
            }
            case 'M':   // SHOW STATISTICS
            {
                DisplayStatistics(hash);
                break;
            }
            case 'Q':   // EXIT PROGRAM + CLEAR STACK + SAVE TO FILES
            {
                //CLEAR STACK of deleted Courses if there is any before exiting
                op.clearStack(stack);
                
                //Save to file before exiting
                IO.saveToFile(treeUnique, treeSecondary, hash);
                
                // User-Interface - A greeting message to user before existing program
                cout << "\n\nThank you for using our services\nGood luck with all your courses!\n";
                
                getchar();
                //Exiting Program
                exit(-1);
                break;
            }
                // User-Interface - Have user reenter until getting a valid entry
            default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
                break;
        }
    } while (toupper(choice[0]) != 'Q');
    return;
}


/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will allow the user to add a
 new Course to the database. It will display an example of
 Course Info, then ask the user to enter all the new
 Course information. If the user enter a CRN that is already
 in the database, it will ask user to enter a different one
 until getting the unique CRN and then modify the info to its
 appropriate format and then insert the Course to the database.
 After the insertion, if successful, display the new Course,
 if fail, then display error message.
 
 ***********************************************************/

void Display::InsertManager(BinarySearchTree<Course> *treeUnique,
                            BinarySearchTree<Course> *treeSecondary, Hash *&hash)
{
    Course* newCourse = new Course();
    string tempStr, repeatInsert;
    
    cout << "\n=================== ADDING A COURSE ====================\n";
    //User-Interface - Give user an example of course info for easiser entry
    cout << "\nExample of Course Information: \n"
    << "\t+ Course CRN: 33380 [positive 5-digit number]" << endl
    << "\t+ Course Name: Data Abstraction and Structures" << endl
    << "\t+ Course Code: CIS 22C" << endl
    << "\t+ Course Department: Computer Information Systems" << endl
    << "\t+ Course Professor: Garbacea, Delia-Manuela [last name, first name]" << endl
    << "\nPlease enter New Course Information!\n";
    int count = 0;
    
    do {
        //Keep asking user to enter a unique CRN
        if (count >= 1)
        {
            cout << "ERROR ==> DUPLICATE Course CRN - This Course CRN " << tempStr << "is already exist in the database!\nPlease enter a non-existed Course CRN!\n";
        }
        cout << "\t+ Course CRN: ";
        tempStr = "";
        tempStr = CRNInputValidation();
        newCourse->setCrn(tempStr);
        count++;
    }while (hash->search(tempStr, *newCourse));
    
    cout << "Thank you! You entered a non-existed CRN.\nPlease proceed with 4 more information for the new Course.\n";
    
    cout << "\t+ Course Name: ";
    tempStr = LineInputModify();    //Capitalize all the first letters
    newCourse->setCourseName(tempStr);
    
    cout << "\t+ Course Code: ";    //Capitalize all letters
    tempStr = CourseCodeInputModify();
    newCourse->setCourseCode(tempStr);
    
    cout << "\t+ Course Department: ";
    tempStr = LineInputModify();    //Capitalize all the first letters
    newCourse->setDepartment(tempStr);
    
    cout << "\t+ Course Professor: ";
    tempStr = LineInputModify();    //Capitalize all the first letters
    newCourse->setProfessorName(tempStr);
    
    //Insert new Course to 2 BST and 1 hash table
    treeUnique->insert(newCourse, compareUnique);
    treeSecondary->insert(newCourse, compareSecondary);
    hash->insert(newCourse);
    
    //Rehash to InsertManager.
    FileIO IO;
    if (hash->getLoadFactor() >= 75) {
        IO.reHash(hash);
    }
    
    //User-Interface: Display the information of the Course just got added to the database
    Course course;
    string temp = newCourse->getCrn();
    //After insert, use hash search to search for the new course to make sure
    //the course fot inserted successfully
    if (hash->search(temp, course))
    {
        cout << "\nNew Course is successfully added:";
        displayOneCourse(course);
    }
    else
    {
        cout << "Error in Adding New Course\n";
    }
    return;
}

/************************************************************
 
 Programmer: Jyh Heng Yu
 Purpose: This function will operates the core executions
 for deleting a certain data in all places (2 BSTs
 and hash). this is designed for a general use of
 deletion throughout the program.
 
 ***********************************************************/
void Display::DeleteCoreCode(string temp, BinarySearchTree<Course> *treeUnique, BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course>& stack)
{
    Course course;
    BinaryNode<Course>* returnedNode = treeUnique->getRootPtr();
    bool resultTree1, resultTree2, remove = false;
    // Search and obtain the information of data deleted.
    course.setCrn(temp);
    treeUnique->getEntry(course, compareUnique, &returnedNode);
    course = *(returnedNode->getItem());
    // DELETE IN TREE 1
    resultTree1 = treeUnique->remove(course, compareUnique);
    // DELETE IN TREE 2
    resultTree2 = treeSecondary->remove(course, compareSecondary);
    // DELETE IN HASH
    remove = hash->remove(temp, course);
    if (remove)
    {
        if (!hash->search(temp, course))
        {
            cout << "Course with CRN " << temp << " is successfully DELETED!\n";
            stack.push(course);
        }
        else
            cout << "Errors occurs in deleteing Course CRN " << temp << endl;
    }
    else
        cout << "Course with CRN " << temp << " is NOT FOUND!\n";
}

/************************************************************
 
 Programmer: Jyh Heng Yu
 Purpose: This function will operates the core executions
 for searching in secondary tree. Designed to work
 as part of the secondary deletion.
 
 ***********************************************************/
bool Display::searchTreeSeondary(Queue<string> & CRNTemp, BinarySearchTree<Course> *treeSecondary, Course item, int & count, string temp)
{
    bool status = false;
    BinaryNode<Course>* returnedNode = treeSecondary->getRootPtr();
    if (treeSecondary->getEntry(item, compareSecondary, &returnedNode))
    {
        count = 1;
        cout << "\nSEARCHING Course Name...\n";
        item = *(returnedNode->getItem());
        displayOneCourse(item);
        CRNTemp.enqueue(item.getCrn());
        
        //search for other duplicates
        returnedNode = returnedNode->getRightPtr();
        while (treeSecondary->getEntry(item, compareSecondary, &returnedNode))
        {
            cout << "\n-----------------------------------------------\n";
            item = *(returnedNode->getItem());
            displayOneCourse(item);
            CRNTemp.enqueue(item.getCrn());
            returnedNode = returnedNode->getRightPtr();
            count++;
        }
        cout << "\n===> FOUND " << count << " match(es).\n";
        status = true;
        return status;
    }
    else
    {
        return status;
    }
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will allow the user to remove a
 Course in the database. It will display an menu of
 two options (remove by CRN, Name, or return to main menu)
 and execute according to input. It then asks user to target
 to be deteled and then modify the info to its appropriate
 format and then search for it in the database. If NOT FOUND,
 then ask again until FOUND. If FOUND, then detele
 the Course and then check whether the Course was deleted
 or not and display a message.
 
 ***********************************************************/

void Display::DeleteManager(BinarySearchTree<Course> *treeUnique,
                            BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course>& stack)
{
    string temp = "", choice = "", CRNTarget = "", tempName = "", decision = "", userEntry = "";
    //bool remove, resultTree1, resultTree2;
    
    do {
        cout <<
        "\n\t __________________________________\n"
        "\t|                                  |\n"
        "\t|            DELETE MENU           |\n"
        "\t|----------------------------------|\n"
        "\t| P. Detele by Course CRN          |\n"
        "\t| S. Detele by Course Name         |\n"
        "\t| U. Undo Delete                   |\n"
        "\t| R. Return to Main Menu           |\n"
        "\t|__________________________________|\n";
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        
        switch (toupper(choice[0]))
        {
            case 'P':
            {
                cout << "Please enter the Course CRN: ";
                CRNTarget = CRNInputValidation();
                DeleteCoreCode(CRNTarget, treeUnique, treeSecondary, hash, stack);
                break;
            }
                
            case 'S':
            {
                int count;
                Course deleteTemp;  // temporarily store data of duplicate deleting datas.
                Course target;  // target data for search / delete
                Queue<string> CRNTemp;
                string continueSelect = "Y";
                bool searchResult;
                
                cout << endl << "Please enter the Course Name: ";
                tempName = LineInputModify();
                target.setCourseName(tempName);
                searchResult = searchTreeSeondary(CRNTemp, treeSecondary, target, count, tempName);
                //SEARCH NOT FOUND
                if (searchResult)
                {
                    // ask user for options.
                    cout << endl << "Enter 'A' to delete all, enter 'S' to delete by selection: ";
                    cin >> decision;
                    
                    while (toupper(decision[0]) != 'A' &&  toupper(decision[0]) != 'S')
                    {
                        cout << "INVALID ENTRY! Please enter a valid entry: ";
                        cin >> decision;
                    }
                    
                    if (toupper(decision[0]) == 'A')
                    {
                        cout << endl << "DELETING all Courses with Name \"" << tempName  << "\"" << endl << endl;
                        for (int num1 = 1; num1 <= count; num1++)
                        {
                            CRNTemp.dequeue(CRNTarget);
                            //Delete each secondary duplicates one by one.
                            DeleteCoreCode(CRNTarget, treeUnique, treeSecondary, hash, stack);
                        }
                        cout << endl << "DELETION COMPLETED!" << endl;
                    }
                    else if (toupper(decision[0]) == 'S')
                    {
                        int num2 = 0;
                        cout << endl << "SELECTION DELETION" << endl;
                        while (toupper(continueSelect[0] == 'Y'))
                        {
                            if (num2 < 2)
                            {
                                cout << "Please enter the class you want to delete (by CRN): ";
                                cin >> userEntry;
                                DeleteCoreCode(userEntry, treeUnique, treeSecondary, hash, stack);
                                num2++;
                                cout << "Do you want to continue? Enter 'Y' to continue or 'Q' to quit: ";
                                cin >> continueSelect;
                            }
                        }
                        cout << endl << "DELETION COMPLETED!" << endl;
                    }
                }
                else
                    cout << "Course with Name " << tempName << " is NOT FOUND" << endl;
                cin.ignore();
                break;
            }
            case 'U': // UNDO DELETE
            {
                UndoDeleteManager(treeUnique, treeSecondary, hash, stack);
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
 
 Programmer: Trinh Nguyen
 Purpose: 
 The user can undo the delete in the reverse order of the
 delete sequence. When the user selects ìSave to fileî,
 the undo stack is cleaned out (no undo possible unless
 more delete occurs first)
 
 ***********************************************************/

void Display::UndoDeleteManager(BinarySearchTree<Course> *treeUnique,
                                BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course> &stack)
{
    Course temp;
    ScreenOutput op;
    //Undo the delete in the reverse order of the delete sequence
    if (op.undoDeleteCourse(treeUnique, treeSecondary, hash, stack, temp)) {
        cout << "Undo Completed! \n"
        << "This coure below is now back to the data.\n";
        displayOneCourse(temp);
    }
    else { //No undo possible unless more delete occurs first
        cout << "NO more Course deletion has been made!\n";
    }
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display statistics of hash table
 
 ***********************************************************/

void Display::DisplayStatistics(Hash *hash)
{
    cout << "\n\t   ~ DISPLAY HASH TABLE STATISTIC ~\n\n";
    cout <<
    "\t ___________________________________\n"
    "\t|                                   |\n"
    "\t|            STATISTICS             |\n"
    "\t|-----------------------------------|\n";
    
    
    hash->statistic();
    return;
}


/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function write data of 2 BST and hash table
 to file
 
 ***********************************************************/

void Display::SaveToFile(FileIO IO, BinarySearchTree<Course> *treeUnique,
                         BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    cout << "\n======> WRITE DATA TO FILE \"" << outFileName << "\"!\n";
    IO.saveToFile(treeUnique, treeSecondary, hash);
    return;
}


/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display a header of a table
 
 ***********************************************************/

void Display::displayHeader()
{
    cout << setw(12) << left << "| CRN"
    << setw(57) << left << "| COURSE NAME"
    << setw(17) << left << "| COURSE CODE"
    << setw(40) << left << "| DEPARTMENT"
    << setw(29) << left << "| PROFESSOR" << right << "|" << endl;
    return;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display information of an Course
 It will be used for displaying a single Course for
 a better presentaion.
 
 ***********************************************************/

void displayOneCourse(Course& anItem)
{
    cout << "\nCourse CRN: " << anItem.getCrn() << endl
    << "Course Name: " << anItem.getCourseName() << endl
    << "Course Code: " << anItem.getCourseCode() << endl
    << "Course Department: " << anItem.getDepartment() << endl
    << "Course Professor: " << anItem.getProfessorName() << endl;
    return;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display information of an Course
 It will be used for displaying a single Course for
 a better presentaion.
 
 ***********************************************************/

void displayCourse(Course& anItem)
{
    cout << "\nCourse CRN: " << anItem.getCrn() << endl
    << "Course Name: " << anItem.getCourseName() << endl
    << "Course Code: " << anItem.getCourseCode() << endl
    << "Course Department: " << anItem.getDepartment() << endl
    << "Course Professor: " << anItem.getProfessorName() << endl;
    return;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function validate user input in order to get
 a valid Course CRN (a 5-digit numnber)
 
 ***********************************************************/

string Display::CRNInputValidation()
{
    string input;
    int crn = 0;
    int count = 0;
    do
    {
        if (count > 0)
            cout << "Please enter a valid 5-digit number Course CRN: ";
        getline(cin, input);
        crn = stoi(input);
        count++;
    } while (crn < 0 || crn > 100000);
    return input;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will modify the user input of
 Course Name + Department and Professor Name by capitalizing
 the first letter of every word to be used for the insertion,
 search and deletion of a course
 Ex: Input: data structures ---> Modify: Data Structures
 Input: computer information systems ---> Modify: Computer Information Systems
 Input: garbarcea, delia-manuela ---> Modify: Garbacea, Delia-Manuela
 
 ***********************************************************/

string Display::LineInputModify()
{
    string input;
    getline(cin, input);
    input[0] = toupper(input[0]);
    for (int i = 0; i <= (int)input.length(); i++)
    {
        if (input[i] == ' ' || input[i] == '-' || input[i] == '(' || input[i] == ':')
        {
            input[i + 1] = toupper(input[i + 1]);
        }
    }
    return input;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will modify the uder input of
 Course Code by capitalizing every letters in the string to
 be used for the insertion, search and deletion of a course
 Ex: Input: cis 22c ---> Modify: CIS 22C
 
 ***********************************************************/

string Display::CourseCodeInputModify()
{
    string input;
    getline(cin, input);
    input[0] = toupper(input[0]);
    for (int i = 0; i < (int)input.length(); i++)
    {
        if (isalpha(input[i]))
            input[i] = toupper(input[i]);
    }
    return input;
}

/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display information of an Course
 It will be used for displaying table for all Courses for a
 better presentaion.
 
 ***********************************************************/
void displayTable(Course& anItem)
{
    cout << "| " << setw(10) << left << anItem.getCrn()
    << "| " << setw(55) << left << anItem.getCourseName()
    << "| " << setw(15) << left << anItem.getCourseCode()
    << "| " << setw(38) << left << anItem.getDepartment()
    << "| " << setw(27) << left << anItem.getProfessorName()
    << right << "|" << endl;
    return;
}


/************************************************************
 
 Programmer: Trinh Nguyen
 Purpose: This function will display information of an Course
 It will be used for displaying a indented tree for a
 better presentaion.
 
 ***********************************************************/
void displayTree(Course& anItem)
{
    cout << anItem.getCrn() << " ------ "
    << anItem.getCourseName() << " ------ "
    << anItem.getCourseCode() << " ------ "
    << anItem.getDepartment() << " ------ "
    << anItem.getProfessorName() << endl << endl;
    return;
}
