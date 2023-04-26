/*****************************************************************
//
//  NAME:        William Evers-Hood                     
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        4/25/2023
//
//  FILE:        llist.h.cpp
//
//  DESCRIPTION:
//   function prototypes for the llist class 
//
****************************************************************/

#include <iostream>
#include "record.h"


class llist
{
private:
    record *    start;
    char        filename[20];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist(const llist&);
    llist();
    llist(char[]);
    ~llist();
    llist& operator=(const llist&);
    /*friend ostream& operator<<(ostream&, const llist&);*/
    void addRecord(int, char [ ],char [ ]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

