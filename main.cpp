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
//  FILE:        main.cpp
//
//  DESCRIPTION:
//   This file contains the main function that will display the user 
//   interface menu and execute all of its options for Project 2 
//
//
****************************************************************/

#include "menuoptions.h"
#include "llist.h"

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function that will display the user 
//                 interface menu and execute its different options
//
//  Parameters:    N/A
//
//  Return values:  0 : success
//
****************************************************************/ 

int main() 
{
    int num;
    llist database;

    do
    {
     	display(num);
        
        if (num == 1)
        {
            option1(database);
        }
	else if (num == 2)
        {
            option2(database);
        }
	else if (num == 3)
        {
            option3(database);
        }
	else if (num == 4)
        {
            option4(database);
        }
	else if (num == 5)
        {
            option5(database);
        }
        else if (num == 6)
        {
            option6(database);
        }
    } while (num != 7);

    database.~llist();
    return 0;
}
