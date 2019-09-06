/*****************************************************************
//
//  NAME:        Ioane Omerod
//
//  HOMEWORK:    Project 1
//
//  CLASS:	 ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 7, 2019
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the structure for a record in the
//   bank's database
//
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};

