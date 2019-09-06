/*****************************************************************
//
//  NAME:        Ioane Omerod
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 12, 2019
//
//  FILE:        menuoptions.cpp
//
//  DESCRIPTION:
//   This file contains the function definitions for the display,
//   option1, option2, option3, option4, option5 and option6 functions
//   for Project 2
//
//
****************************************************************/

#include <limits>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: display
//
//  DESCRIPTION:   A userinterface function that displays the menu
//                 and accepts what option the user wants to use
//
//  Parameters:    option (int &) : the address int where the 
//                                  option picked will be stored
//
//  Return values:  N/A
//
****************************************************************/

void display(int &option)
{
    cout << "Select a task to be done by typing the number \n";
    cout << "corresponding to the option.\n";
    cout << "1. Add a new record in the database.\n";
    cout << "2. Print information about a record using the accountno.\n";
    cout << "3. Print all information in database.\n";
    cout << "4. Print records whose name starts with:\n";
    cout << "5. Delete existing record using accountno.\n";
    cout << "6. Reverse the order of the database and print it.\n";
    cout << "7. Exit.\n";
    cout << "Enter an option: ";
    
    cin >> option;

    while ( cin.fail() || option < 0 || option > 7)
    {
       cin.clear();
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       cout << "Error. Please enter a valid option: ";
       cin >> option;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*****************************************************************
//
//  Function name: option1
//
//  DESCRIPTION:   A userinterface function that executes the 
//                 add a new record option from the menu
//
//  Parameters:    database (llist &) : contains the llist that 
//                                      addRecord will be called for
//
//  Return values:  N/A
//
****************************************************************/

void option1(llist &database)
{
    int accountno;
    char name[25];
    char address[80];
    int nameReturn = 1;
    int namelen;
    int i;

    cout << "Enter accountno: ";
    cin >> accountno;
    
    while ( cin.fail() || accountno < 0)
    {
       cout << "Error. Please enter a positive integer: ";
       cin >> accountno;
       cin.clear();
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    cout << "Insert name: ";
    cin.get(name, 25, '\n');
    
    while ( cin.fail() || (nameReturn == 1) )
    {
        if ( cin.fail() )
        {
            cout << "Error. Enter a valid name: ";
            cin.get(name, 25, '\n');
        }   
        else
        {
     	    namelen = strlen(name);
            for (i = 0; i < namelen; i++)
            {
                if (! (isalpha(name[i]) || name[i] == '-' || name[i] == ' ') )
                {
             	    cout << "Error. Enter a valid name: ";
                    cin.get(name, 25, '\n');
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    i = namelen;
                    nameReturn = 1;
                }
                else
                {
             	    nameReturn = 0;
                }
	    }
        }
    }
 
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    cout << "Type your address and type a ; at the end\n";
    cout << "when you are finished.\n";
    cout << "Insert address: ";
    cin.get(address, 80, ';');
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    database.addRecord(accountno, address, name);
}

/*****************************************************************
//
//  Function name: option2
//
//  DESCRIPTION:   A userinterface function that executes the
//                 print a record option from the menu
//
//  Parameters:    database (llist &) : contains the llist that
//                                      printRecord will be called for
//
//  Return values:  N/A
//
****************************************************************/

void option2(llist &database)
{
    int accountno;

    cout << "Enter accountno: ";
    cin >> accountno;
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    while ( cin.fail() || accountno < 0 )
    {
       cout << "Error. Please enter a positive integer: ";
       cin >> accountno;
       cin.clear();
       cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    database.printRecord(accountno);
}

/*****************************************************************
//
//  Function name: option3
//
//  DESCRIPTION:   A userinterface function that executes the
//                 print all records option from the menu
//
//  Parameters:    database (llist &) : contains the llist that
//                                      << will be used with
//
//  Return values:  N/A
//
****************************************************************/

void option3(llist &database)
{
    cout << database;
}

/*****************************************************************
//
//  Function name: option4
//
//  DESCRIPTION:   A userinterface function that executes the
//                 find and then print a record option from 
//                 the menu
//
//  Parameters:    database (llist &) : contains the llist that
//                                      findRecord will be called for
//
//  Return values:  N/A
//
****************************************************************/

void option4(llist &database)
{
    char name[25];
    int namelen;
    int i;
    int nameReturn = 1;

    cout << "Enter beginning of name: ";
    cin.get(name, 25, '\n');
    cout << "Here\n";
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    while ( (nameReturn == 1) )
    {
     	namelen = strlen(name);
        for (i = 0; i < namelen; i++)
        {
            if (! (isalpha(name[i]) || name[i] == '-' || name[i] == ' ') )
            {
                cout << "Error. Enter a valid name: ";
                cin.get(name, 25, '\n');
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                i = namelen;
                nameReturn = 1;
            }
            else
            {
             	nameReturn = 0;
            }
	}
    }

    database.findRecords(name);
}

/*****************************************************************
//
//  Function name: option5
//
//  DESCRIPTION:   A userinterface function that executes the
//                 delete a record option from the menu
//
//  Parameters:    database (llist &) : contains the llist that
//                                      deleteRecord will be called for
//
//  Return values:  N/A
//
****************************************************************/

void option5(llist &database)
{
    int accountno;

    cout << "Enter accountno: ";
    cin >> accountno;
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    while ( cin.fail() || accountno < 0 )
    {
       cout << "Error. Please enter a positive integer: ";
       cin >> accountno;
       cin.clear();
       cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    database.deleteRecord(accountno);
}

/*****************************************************************
//
//  Function name: option6
//
//  DESCRIPTION:   A userinterface function that executes the
//                 reverse a database option from the menu
//
//  Parameters:    database (llist &) : contains the llist that
//                                      reverse will be called for
//
//  Return values:  N/A
//
****************************************************************/

void option6(llist &database)
{   
    database.reverse();
    cout << database;
}
