/*****************************************************************
//
//  NAME:        Ioane Omerod
//
//  HOMEWORK:    Project 2
//
//  CLASS:	 ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 12, 2019
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file contains the llist function declarations for
//   Project 2
//
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H 

#include <iostream>
#include "record.h"

using namespace std;

class llist
{
  private:
    record *    start;
    char        filename[16];
    int         readfile();
    void        writefile();
    record *    reverse(record * );
    void        cleanup();

  public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord (int, char [ ],char [ ]);
    int printRecord (int);
    friend ostream& operator<< (ostream&, llist&);
    int findRecords (char [ ]);
    int deleteRecord(int);
    void reverse();
    llist & operator= (const llist&);
    llist (const llist&);
};

#endif
