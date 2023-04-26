#include "llist.h"
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>

/************************************************
 class: ics 212
 
 prof: Ravi Narayan
 
 Name: William Evers-Hood 
 
 Date 4/22/2023

 File: llist.cpp
 
 Purpose: this file contains the definitions of the llist
          class methods
 *************************************************/


#ifdef DEBUG
#define debug(x) std::cout << x << std::endl;
#else
#define debug(x)
#endif




/*****************************************************************
//
//  Function name: llist::llist()
//
//  DESCRIPTION:   This function initializes instance variable of the llist object
//                 type 
//           
//  Parameters:     this: reference to the object being initialized 
//
//  Return values:  none
//
****************************************************************/

llist::llist()
{
this->start = NULL;
strcpy(this->filename, "bankstorage.txt");
llist::readfile();
}
/*****************************************************************
//
//  Function name: llist::llist(char filename[])
//
//  DESCRIPTION:   This function initializes instance variable of the llist object
//                 type given a filename to open and read value from at run-time
//           
//  Parameters:    char filename[]: name of a file to be opened and read by 
//                                  reafile onto a llist object
//                 this: reference to the object calling the destructor
//  Return values: none
//
****************************************************************/


llist::llist(char filename[])
{
strcpy(this->filename, filename);
this->start = NULL;
llist::readfile();
}


/*****************************************************************
//
//  Function name: llist::llist(const llist&)
//
//  DESCRIPTION:   This function initializes instance variable of the llist object
//                 type [by copying a list from one given list onto another list
//           
//  Parameters:    const llist&: reference type to an llist object. this is object being copied
//                 this: reference to the object calling the destructor
//  Return values:  none
//
****************************************************************/


llist::llist(const llist& copy)
{
    int counter;
    struct record *current, *copycurrent, *addition;
    counter = 0;
    copycurrent = copy.start;
    this->start = new struct record;
    current = this->start;
    copycurrent = copy.start;
    do
    {
        counter++;
        (*current).accountno = (*copycurrent).accountno;
        strcpy((*current).name, (*copycurrent).name);
        strcpy((*current).address, (*copycurrent).address);
        copycurrent = (*copycurrent).next;
        if (copycurrent != NULL && (*current).next == NULL)
        {
            addition = new struct record;
            (*current).next = addition;
            current = (*current).next;
        }
    } while (copycurrent != NULL);
 
}

/*****************************************************************
//
//  Function name: llist::~llist()
//
//  DESCRIPTION:   This function removes object of llist datatype from storing any values on the heap
//           
//  Parameters:     this: reference to the object calling the destructor
//
//  Return values:  none
//
****************************************************************/



llist::~llist()
{
    llist::writefile();
    llist::cleanup();
    this->start = NULL;
}
 
/*****************************************************************
//
//  Function name: llist::operator=(const llist& copy)
//
//  DESCRIPTION:   This function takes an instance of an llist object 
//                 and copies into another llist object either filling it 
//                 or overwritting what already occupied the list
//           
//  Parameters:    const llist&: constant referecne type to an llist object
//                              to be copied and read from but not manipulated
//
//  Return values:  returns by reference a llist object with copied values
//
****************************************************************/


llist& llist::operator=(const llist& copy)
{
    int counter;
    struct record *current, *copycurrent, *addition;
    counter = 0; 

    if(this != &copy)
    {
        if(this->start == NULL)
        {
            start = new struct record;
        }
        current = this->start;
        copycurrent = copy.start;
        do
        {
            counter++;
            (*current).accountno = (*copycurrent).accountno;
            strcpy((*current).name, (*copycurrent).name);
            strcpy((*current).address, (*copycurrent).address);
            copycurrent = (*copycurrent).next;
            if (copycurrent != NULL && (*current).next == NULL)
            {
                addition = new struct record;
                (*current).next = addition;
                current = (*current).next;
            }
        } while (copycurrent != NULL); 
    }
    return *this;
}

/********************************************************** 
class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: addrecord

purpose: adds record to a linked list data base stored on the heap

parameters:  int uaccountno: the account number of the record to be added, used to tell where in the database the     records is to be stored
            char unamme[]: character array contianing the name of the account holder
            char uaddress[]: character array containing the address of the account holder 
 
return: -1: was not able to add the record for whatever reason
         0: successfully added the record
 
************************************************************/

void llist::addRecord(int uaccountno, char uname[ ],char uaddress[ ])
{
    struct record *current, *coming, *addition;              
    if (start == NULL)
    {
        start = new(struct record);
        (*start).accountno = uaccountno; 
        strcpy((*start).name, uname);
        strcpy((*start).address, uaddress);
        (*start).next = NULL;
        return;
    }
    addition = new(struct record);
    (*addition).accountno = uaccountno;
    strcpy((*addition).name, uname);
    strcpy((*addition).address, uaddress);
    (*addition).next = NULL;
    if(uaccountno < (*start).accountno)
    {
        current = (start); 
        (start) = addition;
        (*start).next = current;
        return;
    }
    current = (start);
    coming = (*current).next;
    if(coming == NULL)
    {
        (*start).next = addition;
        return;
    }
    if (uaccountno < (*coming).accountno)
    {
        (*current).next = addition;
        (*addition).next = coming;
    return;
    }
    while(coming != NULL)
    {
        current = coming; 
        coming = (*current).next;
        if(coming == NULL)
        {
            (*current).next = addition;
            return; 
        }  
        if(uaccountno < (*coming).accountno)
        {
            (*current).next = addition;
            (*addition).next = coming;
            return;
        }                             
    }
}

/***********************************

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: llist::findRecord

purpose: prints all records in the heap to the command line 

Parameters
            
return: -1: was not able to find the record for whatever reason
          0: successfully found the records
************************************/


int llist::findRecord(int uaccountno)
{
    int trig, none, counter;
    struct record *current;
    counter = 0;
    trig = -1;
    if((start) == NULL)
    {
        return trig;
    }
    current = start;
    trig = 1;    
    do
    {
        none = 1;
        if (uaccountno == (*current).accountno)
        {
            counter++;
            trig = 0;
            std::cout << "account number " << (*current).accountno << std::endl;
            std::cout << "address  " << (*current).address << std::endl;
            std::cout << "name " << (*current).name << std::endl;
            current = (*current).next;
            none = 0;
        }
        if (none == 1)
        {
            current = (*current).next;
        }
    } while (current != NULL);
    debug("debug mode for find record: # of record printed " << counter);
    return trig;
}




/**************************************

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: addrecord

purpose: prints all records in the heap to the command line 

parameters: struct record * start: keeps track of the beginning of the list and is stored on the stack
            
return: void
************************************/


void llist::printAllRecords()
{
    int counter;
    struct record *current;
    counter = 0; 
    current = start;
    if (start == NULL)
    {
        std::cout << "empty list " << std::endl;
        return;
    }
    do
    {
        counter++;
        std::cout << "account number: " << (*current).accountno << std::endl;
        std::cout << "name: " << (*current).name << std::endl;
        std::cout << "address: " << (*current).address << std::endl;
        current = (*current).next;
    } while (current != NULL);
    debug("printall debug mode: # of record printed " << counter);

}

/************************************************
 class: ics 212
 
 prof: Ravi Narayan
 
 Name: William Evers-Hood 
 
 Function: deleterecord
 
 purpose: deletes record from a linked list data base stored on the heap
 
 parameters: int uaccountno: the account number of the record to be added, used to tell where in the database the     records is to be stored
 
 return: -1: was not able to delete the record for whatever reason
          0: successfully deleted the record 
*************************************************/

int llist::deleteRecord(int uaccountno)
{
    int trig, none, startdel, counter;
    struct record *current, *coming, *remove;
    trig = -1;
    counter = 0;                                                
    if((start) == NULL)
    {
        return trig;
    }
    if((*start).next == NULL && (*start).accountno != uaccountno)
    {
        return trig;
    } 
    current = start;
    coming = (*start).next;
    trig = 1;
    do
    {   
        startdel = 0;
        none = 1;
        while (uaccountno == (*current).accountno)
        {
            counter++;
            trig = 0;
            (start) = (*current).next;
            delete(current);
            current = start;
            if((current == NULL))
            {
                return trig;
            }
            coming = (*current).next;
            none = 0;
            startdel = 1;
        } 
        if(coming != NULL)
        {
            if(uaccountno == (*coming).accountno && startdel == 0)
            {
                counter++;
                remove = (*current).next; 
                coming = (*remove).next; 
                (*current).next = coming;
                delete(remove);
                trig = 0;
                none = 0;
            }
        }
        if (none == 1)
        {
            current = (*current).next;
            coming = (*coming).next; 
        }
    } while (coming != NULL);
    debug("delete method debug: # of file deleted " << counter);
    return trig;
}
/***********************************
 
class: ics 212
 
prof: Ravi 
 
Name: William Evers-Hood 
 
Function: cleanup
 
purpose: deallocates all heap space when main exits 
 
Parameters
             
return: void
***********************************/

void llist::cleanup()
{
    struct record *current, *coming; 
    int counter;
    current = start;
    counter = 0;
    if((start) == NULL)
    {
        return;
    }   
    do 
    {
        counter++;
        coming = (*current).next;
        delete(current);
        current = (coming);
    } while (current != NULL);
    debug("cleanup debug mode: " << counter << " records deallocatted from heap");
    (start) = NULL;
}


/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION: read file reads information from a txt file and puts it into an llist
//               object 
//
//  Parameters:  none
//
//  Return values:  0 : file was opened and contents were read
//                 -1 : file was not able to be opened 
//
****************************************************************/



int llist::readfile()
{
    int trig, accountnoPrime, counter, flip;
    long i;                                                  
    char namePrime[30];
    char addressPrime[50];
    char trash[10];
    counter = 0;
    trig = 0;
    flip = 1; 
    i = 0;
    std::ifstream infile;
    infile.open(this->filename, std::ios::in);
    if (infile.is_open())
    {
    debug("debug activated for readfile");
        do
        {
            infile >> accountnoPrime;
            if(infile.fail())
            {
            flip = 0;
            }
            if (accountnoPrime == 0)
            {
                flip = 0;
            }
            infile.getline(trash, 10);
            infile.getline(namePrime, 30);
            trig = 0;
            counter = 0;
            while(counter < 50 && trig < 3)
            {   
                addressPrime[counter] = infile.get();
                if (addressPrime[counter] == 47)
                {
                    trig++;
                }
                counter++;     
            }
            addressPrime[counter - 3] = '\0';
            debug("account number " << accountnoPrime);
            debug("name " << namePrime);
            debug("address " << addressPrime);
            
            if(flip == 1)
            {
                addRecord(accountnoPrime, namePrime, addressPrime);
            }
            i++;

        } while(flip == 1);
    }
    else
    {
        return -1;
    }
return 0;
                           
}
    
/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   writes to a file with the contents of an llist object
//
//  Parameters:    none
//
//  Return values:  0 : file was opened and contents were added sucessfully
//                 -1 : file was not opened
//
****************************************************************/

int llist::writefile()
{
    struct record *current;
    char addressPrime[50];
    int trig;
    trig = -1;
    current = start;
    if(start == NULL)
    {
        return trig;
    }  
    std::ofstream outfile;
    outfile.open(this->filename, std::ios::out);
    if(outfile.is_open() == false)
    {
        return trig;
    }    
    do
    {
        debug("debug mode accountno: " << (*current).accountno);
        debug("debug mode name: " << (*current).name);
        debug("debug mode address: " << (*current).address);
        debug("debug done");
        outfile << (*current).accountno << std::endl;
        outfile << (*current).name << std::endl;
        strcpy(addressPrime, (*current).address);
        strcat(addressPrime, "///");
        strcpy((*current).address, addressPrime);
        outfile << addressPrime << std::endl;
        current = (*current).next;        
    } while (current != NULL);
    outfile.close();
    return trig;
}




/*****************************************************************
//
//  Function name: operator<<
//
//  DESCRIPTION:   overloads the << operator to replace the print all function
//
//  Parameters:    ostream& object: the stream that llist information will be put into
//                 const llist&: read only llist object that provides info to be printed
//
//  Return values:  ostream& : returns information to be printed
//
****************************************************************/


/*ostream& operator<<(ostream& out, const llist& input)
{
    struct record *current;
    if (input.start == NULL)
    {
        return out;
    }
    else
    {
        current == input.start
        do
        {
        out << "account number " << current.accountno << std::endl;
        out << "name " << current.name << std::endl;
        out << "address " << current.address << std::endl;
        }while(current != NULL);
        return out;
    }
}*/
