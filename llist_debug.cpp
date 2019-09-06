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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains the llist functions definitions for 
//   Project 2 
//
//
****************************************************************/

#include <fstream>
#include <iostream>
#include <cstring>
#include "llist.h"
#define debug

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   A constructor that will create an llist 
//
//  Parameters:    N/A
//
//  Return values:  N/A
//
****************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename, "project2.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist  
//
//  DESCRIPTION:   A constructor that will create an llist using
//                 a user given filename                             
//
//  Parameters:    ufilename (char [ ]) : contains the filename  
//                                        that will be used in           
//     	       	       	       	       	  the readfile and 
//                                        writefile for this llist
//
//  Return values:  N/A
//
****************************************************************/

llist::llist(char ufilename[ ])
{
    #ifdef debug
        cout << "Constructor called with filename: " << ufilename << '\n';
    #endif

    start = NULL;
    strcpy(filename, ufilename);
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   A copy constructor that will create a copy of 
//                 an llist
//
//  Parameters:    udatabase (llist &) : contains the llist
//                                       that a copy will
//                                       be made of 
//
//  Return values:  N/A
//
****************************************************************/

llist::llist(const llist& udatabase)
{
    record *ustart = udatabase.start;
    if (ustart == NULL)
    {
        start = NULL;
    }
    else 
    {
        record *temp;
        record *tempNext;
        record *utemp;

        start = new record;
        (*start).accountno = (*ustart).accountno;
        strcpy((*start).name, (*ustart).name);
     	strcpy((*start).address, (*ustart).address);
        (*start).next = NULL;

        temp = start;
        tempNext = (*start).next;
        utemp = (*ustart).next;
        
        while (utemp !=  NULL)
        {
            tempNext = new record;
            (*temp).next = tempNext;
            (*tempNext).accountno = (*utemp).accountno;
            strcpy((*tempNext).name, (*utemp).name);
            strcpy((*tempNext).address, (*utemp).address);
            (*tempNext).next = NULL;
            utemp = (*utemp).next;
            temp = tempNext;
            tempNext = (*temp).next;
	}
    }
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   A destructor that will call cleanup and writefile
//                 to free any heap memory
//                 used by the llist and write the llist to 
//                 a file
//
//  Parameters:    N/A
//
//  Return values:  N/A
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   A function that reads from a file and into 
//                 a list of records
//
//  Parameters:    N/A
//
//  Return values:  returnValue : returns number of records written to file
//                                or -1 if the file was not written
//                                to
//
****************************************************************/

int llist::readfile()
{
    ifstream infile;
    infile.open(filename);
    int returnValue = 0;
    int accountno;
    char name[25];
    char address[80];
    int addReturn;
    char c;

    #ifdef debug
        cout << "Readfile used with filename: " << filename << '\n';
    #endif

    if (infile.is_open())
    {
     	while(infile >> accountno)
        { 
            infile.get(c);
            infile.getline(name, 25, '\n');
            infile.getline(address, 80, '\n');
            addReturn = addRecord(accountno, address, name);
            
            if (addReturn == 0)
            {
             	returnValue ++;
            }
	}
    }
    else
    {
     	returnValue = -1;
    }

    infile.close();
    return returnValue;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   A function that writes a list of records into
//                 a file
//
//  Parameters:    N/A
//
//  Return values:  N/A
//
****************************************************************/

void llist::writefile()
{
    ofstream outfile;
    int returnValue;
    struct record *temp;
    temp = start;
    
    #ifdef debug
        cout << "Writefile called with filename: " << filename << '\n';
    #endif

    if ( strcmp(filename, "") )
    {
        outfile.open(filename);
        if (outfile.is_open())
        {
            while (temp != NULL)
            {
                outfile << (*temp).accountno << '\n';
                outfile << (*temp).name << '\n';
                outfile << (*temp).address << '\n';
                returnValue ++;
                temp = (*temp).next;
            }
        }

        outfile.close();
    }

    strcpy(filename, "");
}

/*****************************************************************
//
//  Function name: operator <<
//
//  DESCRIPTION:   A function that prints all records in the database 
//                 and prints the function and its parameters 
//
//  Parameters:    ostream& os : contains the ostream the records
//                               will be printed to
//                 
//                 llist& database : contains the llist whose
//                                   records will be printed  
//                  
//  Return values:  N/A
//
****************************************************************/

ostream & operator<< (ostream& os, llist& database)
{
    record *temp = database.start;
    
    #ifdef debug
        cout << "Print all called with address: " << temp << '\n';
    #endif

    if(temp == NULL)
    {
        os << "Database is empty.\n";
    }
    else
    {
        while(temp != NULL)
        {
            os << "Account Number: " << (*temp).accountno << '\n';
            os << "Name: " << (*temp).name << '\n';
            os << "Address: " << (*temp).address << '\n';
            temp = (*temp).next;
            #ifdef debug
                cout << "Print all's next address:  " << temp << '\n';
            #endif
        }
    }
    return os;
}

/*****************************************************************
//
//  Function name: operator =
//
//  DESCRIPTION:   A function that sets an llist equal to another
//
//  Parameters:    llist& database : contains the llist that
//                                   the second llist will be 
//                                   made equal to
//
//  Return values:  N/A
//
****************************************************************/

llist & llist::operator= (const llist &udatabase)
{
    record *ustart = udatabase.start;

    if (ustart == NULL)
    {
     	cleanup();
        start = NULL;
    }
    else
    {
     	record *temp;
        record *tempNext;
        record *utemp;
     
        if (start == NULL)
        {
            start = new record;
            (*start).next = NULL;
        }

        (*start).accountno = (*ustart).accountno;
        strcpy((*start).name, (*ustart).name);
        strcpy((*start).address, (*ustart).address);

        temp = start;
        tempNext = (*start).next;
        utemp = (*ustart).next;

        while (utemp !=  NULL)
        {
            if (tempNext == NULL)
            {
                tempNext = new record;
                (*temp).next = tempNext;
                (*tempNext).accountno = (*utemp).accountno;
                strcpy((*tempNext).name, (*utemp).name);
                strcpy((*tempNext).address, (*utemp).address);
                (*tempNext).next = NULL;
            }
            else
            {
                (*tempNext).accountno = (*utemp).accountno;
                strcpy((*tempNext).name, (*utemp).name);
                strcpy((*tempNext).address, (*utemp).address);
            }
            utemp = (*utemp).next;
            temp = tempNext;
            tempNext = (*temp).next;
        }
    }
    return *this;
}

/*****************************************************************
//
//  Function name: reverse
//
//  DESCRIPTION:   A function that recursively reverses an
//                 llist 
//
//  Parameters:    node : a record * where the reversing of
//                        an llist will start
//
//  Return values:  temp : a record * so the llist can be reversed
//                         recursively
//
****************************************************************/
 
record * llist::reverse(record *node)
{
    record *temp;
    record *tempNext;
    int checkStart; 
    temp = node;
    checkStart = 1; 
    
    #ifdef debug
        cout << "Reverse called with address: " << node << '\n';
    #endif

    if ( (temp == start) )
    {
        checkStart = 0;
    }
    if (temp != NULL)
    {
        if ( (*temp).next == NULL)
        {
            start = temp; 
        }
        else 
        {
            tempNext = reverse( (*temp).next );
            (*tempNext).next = temp;

            if (checkStart == 0)
            {
                (*temp).next = NULL;
            }
        }
    }
    else 
    {
        cout << "No database to reverse.\n";
    }

    return temp;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   The cleanup function that will free any memory  
//                 on the heap
//
//  Parameters:    N/A
//
//  Return values:  N/A
//
****************************************************************/ 

void llist::cleanup()
{
    if (start != NULL)
    {
     	struct record *temp;
        struct record *tempNext;
        temp = start;

        while (temp != NULL)
        {
            #ifdef debug
                cout << "Cleanup deleting record at address: " << temp << '\n';
            #endif
            tempNext = (*temp).next;
            delete temp;
            temp = tempNext;
        }
        start = NULL;
    }
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   A function called to add a record to a database
//                 and prints the function and its parameters while
//                 in debugmode 
//
//  Parameters:    accountno (int) : account number of
//                                   the record
//                 
//                 name (char [ ])  : name of the person
//                                    in the record
//
//                 address (char [ ]) : address of the person
//                                      in the record
//
//  Return values:  0 : success
//                 -1 : failure
//
****************************************************************/

int llist::addRecord (int accountno, char address[ ],char name[ ])
{
    int returnValue = 0;
   
    #ifdef debug
        cout << "AddRecord called with accountno: " << accountno << '\n';
        cout << "AddRecord called with name: " << name << '\n';
        cout << "AddRecord called with address: " << address << '\n';
    #endif

    if (start == NULL)
    {
        start = new record;
        (*start).accountno = accountno;
        strcpy((*start).name, name);
        strcpy((*start).address, address);
        (*start).next = NULL;
    }
    else
    {
     	struct record *temp;
        struct record *tempNext;
        temp = start;
        tempNext = (*temp).next;
        if (tempNext == NULL)
        {
            if ((*temp).accountno == accountno)
            {
             	returnValue = -1;
            }
            else
            {
             	tempNext = new record;
                (*temp).next = tempNext;
                (*tempNext).accountno = accountno;
                strcpy((*tempNext).name, name);
                strcpy((*tempNext).address, address);
                (*tempNext).next = NULL;
            }
	}
	else
	{
            while (tempNext != NULL)
            {
                if ((*temp).accountno == accountno)
                {
                    returnValue = -1;
                }

                temp = tempNext;
                tempNext = (*temp).next;
            }

     	    if ((*temp).accountno == accountno)
            {
                returnValue = -1;
            }

            if (returnValue == 0)
            {
             	tempNext = new record;
                (*tempNext).accountno = accountno;
                strcpy((*tempNext).name, name);
                strcpy((*tempNext).address, address);
                (*tempNext).next = NULL;
                (*temp).next = tempNext;
                temp = tempNext;
                tempNext = (*temp).next;
            }

	temp = NULL;
        tempNext = NULL;
        }
    }
    if (returnValue == 0)
    {
     	std::cout << "Record added successfully.\n";
    }
    else
    {
     	std::cout << "Record not added.\n";
    }

    return returnValue;
}

/*****************************************************************
//
//  Function name: printRecord
//
//  DESCRIPTION:   A function that prints a record in the database 
//                 and then prints the function and its parameters 
//
//  Parameters:     accountno (int) : contains the account 
//                                    number of the record
//
//  Return values:  0 : success
//                 -1 : failure
//
****************************************************************/

int llist::printRecord (int accountno)
{
    #ifdef debug
        cout << "PrintRecord called with accountno: " << accountno << '\n';
    #endif

    int returnValue;

    if (start == NULL)
    {
     	returnValue = -1;
    }
    else
    {
     	returnValue = -1;
        struct record *temp;
        temp = start;
        
        do
	{
            if ((*temp).accountno == accountno)
            {
             	cout << "Account Number: " << (*temp).accountno << '\n';
                cout << "Name: " << (*temp).name << '\n';
                cout << "Address: " << (*temp).address << '\n';
                returnValue = 0;
            }

            temp = (*temp).next;
        }
	while(temp != NULL);

        temp = NULL;
    }

    if (returnValue != 0)
    {
     	cout << "No such record found\n";
    }

    return returnValue;
}

/*****************************************************************
//
//  Function name: findRecords
//
//  DESCRIPTION:   A function that finds a record in the database 
//                 and prints the function and its parameters 
//
//  Parameters:    name (char [ ]) : contains the name on
//                                   the record
//
//  Return values:  0 : success
//                 -1 : failure
//
****************************************************************/

int llist::findRecords (char name[ ])
{
    #ifdef debug
        cout << "FindRecord called with key: " << name << '\n';
    #endif

    int returnValue;

    if (start == NULL)
    {
     	returnValue = -1;
    }
    else
    {
     	struct record *temp;
        int i;
	int length;
        temp = start;
        length = strlen(name);

        while(temp != NULL)
        {
            for(i = 0; i < length; i++)
            {
             	if (name[i] == (*temp).name[i])
                {
                    returnValue = 0;
                }
                else
                {
                    returnValue = -1;
                    i = length;
                }
            }

            if (returnValue == 0)
            {
             	cout << "Account Number: " << (*temp).accountno << '\n';
                cout << "Name: " << (*temp).name << '\n';
                cout << "Address: " << (*temp).address << '\n';
            }

            temp = (*temp).next;
        }

	temp = NULL;
    }

    if (returnValue != 0)
    {
     	cout << "Records not found\n";
    }

    return returnValue;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   A function that prints a record in the database
//                 and prints the function and its parameters 
//
//  Parameters:    accountno (int) : contains the account 
//                                   number of the record
//
//  Return values:  0 : success
//                 -1 : failure
//
****************************************************************/

int llist::deleteRecord(int accountno)
{
    #ifdef debug
        cout << "DeleteRecord called with accountno: " << accountno << '\n';
    #endif

    int returnValue;

    if (start == NULL)
    {
     	returnValue = -1;
    }
    else
    {
     	struct record *temp;
        struct record *tempPrev;
        temp = start;
        tempPrev = NULL;
        returnValue = -1;

        while (temp != NULL)
        {
            if ((*temp).accountno == accountno)
            {
             	struct record *tempNext;
                tempNext = (*temp).next;
                delete temp;
                temp = NULL;

                if (tempPrev != NULL)
                {
                    (*tempPrev).next = tempNext;
                }
                else
                {
                    if (tempNext != NULL)
                    {
                     	start = tempNext;
                    }
                    else
                    {
                        start = NULL;
                    }
                }
                returnValue = 0;
            }
            else
            {
             	tempPrev = temp;
                temp = (*temp).next;
            }
	}

	temp = NULL;
        tempPrev = NULL;
    }

    if (returnValue == 0)
    {
     	cout << "Record deleted successfully.\n";
    }
    else
    {
        cout << "No such record found.\n";
    }

    return returnValue;
}

/*****************************************************************
//
//  Function name: reverse
//
//  DESCRIPTION:   A function that calls the private reverse
//                 function to reverse a llist 
//
//  Parameters:    N/A
//
//  Return values:  N/A
//
****************************************************************/

void llist::reverse()
{
    reverse(start);
}
