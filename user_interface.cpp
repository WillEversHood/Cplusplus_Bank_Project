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
//  DATE:        04/25/2023
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   contains the user interface that a user will access to interface with
//   the database functionalities of this program
//
****************************************************************/


#include <iostream>
#include <cstring> 
#include "llist.h"

#ifdef DEBUG
#define debug(x) std::cout << x << std::endl;
#else
#define debug(x)
#endif
/*fix orginization*/
 void getAddress(char [], int);
 void getName(char [], int);
 int getFileNum();
/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Don't forget to describe what your main
//                 function does.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : some meaning
//                 -1 : some meaning
// notes for tm put fgets at end of functions so that buffers clear
// fix the broken loop in the get address function 
// comments 
****************************************************************/



int main(int argc, char* argv[])
{    
    int  size, i, acctNum, addressSize, nameSize, quitter, task, validInput;

    char name[20];
    char address[30];
    char options[10];

    char add[] = "add";
    char printall[] = "printall";
    char find[] = "find";
    char delet[] = "delete";
    char quit[] = "quit";
    char  debug[] = "debug";
    addressSize = 100;
    nameSize = 30; 
    quitter = 1;
    validInput = 1;
    /* constructor */
    llist datalist;
    std::cout << "Welcome to the bank user interface" << std::endl;
    std::cout << "Options include 'add' to add a record" << std::endl;
    std::cout << "'printall' to print all records" << std::endl;
    std::cout << "'find' to find a record" << std::endl;
    std::cout << "'delete' to delete a record" << std::endl;
    std::cout << "'quit' to quit the program" << std::endl;
    std::cout << "type and enter the name of an option to proceed" << std::endl;
    if (argc != 1)
    {
        if (argc > 2)
        {
            quitter = 0;
            std::cout << "invalid command line input" << std::endl;
        }
        else if(strcmp(argv[1], debug) != 0)
        {
           quitter = 0;
           std::cout << "invalid command line input" << std::endl;
        }
        else
        { 

            std::cout << "in debug mode" << std::endl;
        }
    }

    while (quitter == 1)
    {
        task = 1;
        validInput = 1;
        std::cin >> options;
      /*  std::cin.ignore();*/
        size = strlen(options);
        switch(options[0])
        {
            case 'a':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(add, options, size) != 0)
                    {
                        validInput = 0;
                    }
                }
                if (validInput == 1)
                {
                    /*  link and print */
                    acctNum = getFileNum();
                    getAddress(address, addressSize);
                    getName(name, nameSize);
                    /*interface with database*/
                    datalist.addRecord (acctNum, name, address);
                    std::cout << "record addition complete" << std::endl;
                }
                else 
                {
                    std::cout << "please enter valid input" << std::endl;
                }     
                break;   
                case 'p':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(printall, options, size) != 0)
                    {
                        validInput = 0;
                    }
                }
                if (validInput == 1)
                {
                    /*  link and print */
                    std::cout << "printing all records" << std::endl;
                    datalist.printAllRecords();
                    std::cout << "done" << std::endl;
                }
                else 
                {
                    std::cout << "please enter valid input" << std::endl;
                }             
                break; 
                case 'f':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(find, options, size) != 0)
                    {
                        validInput = 0;
                    }
                }
                if(validInput == 1)
                {
                    std::cout << "finding account info" << std::endl;
                    task = datalist.findRecord(getFileNum());
                    if (task != 0)
                    {
                        std::cout << "please enter valid account info to find" << std::endl;
                    }
                    else 
                    {    
                        std::cout << "account found" << std::endl;
                    }
                } 
                else
                {
                    std::cout << "please enter valid input" << std::endl; 
                }      
                break; 
                case 'd':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(delet, options, size) != 0)
                    {
                    validInput = 0; 
                    }
                }
                    if(validInput == 1)
                    {
                        std::cout << "deleting account info" << std::endl;
                        task = datalist.deleteRecord(getFileNum()); 
                        if (task != 0)
                        {
                            std::cout << "please enter valid account info to delete" << std::endl;
                        }
                        else
                        { 
                            std::cout << "account deleted" << std::endl; 
                        }
                    } 
                    else 
                    {
                        std::cout << "please enter valid input" << std::endl;
                    }
                break; 
                case 'q':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(quit, options, size) != 0)
                    {                 
                        /*  link and print */
                        validInput = 0;        
                    } 
                }
                if(validInput == 1) 
                {
                    std::cout << "program exiting" << std::endl;
                    quitter = 0;
                }
                else 
                {
                    std::cout << "please enter valid input" << std::endl;
                }
            break; 
            default:
               {
                   std::cout << "plese insert acceptable input" << std::endl;
               }  
           break;
           }   
    }
    datalist.~llist();
    return 0;
}

/*****************************************************************
//
//  Function name: getFileNum()
//
//  DESCRIPTION:   This function uses a while loop to get a single positve int value
//                 to take as a file num
//
//           
//  Parameters:     none
//
//  Return values: int a file number
//
****************************************************************/

int getFileNum()
{
    int account, trigger;
    std::string trash;
    trigger = 1;
    std::cout << "please enter valid account number" << std::endl;
    while (trigger == 1)
    {
        std::cin >> account;
        if( account > 0) 
        {
            trigger = 0;
        }
        else 
        {
            //parses one char at a time from the buffer so it prints error multiple times
            std::cout << "invalid accountnumber try again" << std::endl; 
            std::cin.clear();
            std::cin.ignore();         
        }
    }
    debug("\nDebug info");
    debug("getFileNum output " << account);
    return account;
}


/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   This function uses a loop and fgets in combination
//                 with an exit sequence to get a multi line address 
//                 with multiple newlines //
//  Parameters:    char * pointer to array addressPrime[] storing, int Size: the size of the //                 char array 
//
//  Return values: none 
//
****************************************************************/



void getAddress(char addressPrime[], int size)
{
    int trig, counter;
    std::string trash;
    counter = 0;
    trig = 0;
    std::cin.ignore(100, '\n');
    std::cout << "please enter your address\n Enter /// when complete " << std::endl; 
    while(counter < size && trig < 3)
    {
        addressPrime[counter] = std::cin.get();
        if (addressPrime[counter] == 47)
        {
            trig++;
        }
        counter++;
    }
    addressPrime[counter - 3] = '\0';
    debug("\nDebug info");
    debug("Address: " << addressPrime);
    debug("Address Length: " << strlen(addressPrime));
    return;
}

/*****************************************************************
//
//  Function name: getName
//
//  DESCRIPTION:   function that gets a string name value that is ended
//                 when the user enter newline
//
//  Parameters:    char* namePrime[]: this is the array that the name will be stored in
//                 int size: size lets the functio nknow how big the array is
//
//  Return values: none
//
****************************************************************/


void getName(char namePrime[], int size)
{
    int trig, counter;
    counter = 0;
    trig = 1;
    std::cin.ignore(100, '\n');
    std::cout << "please enter your name" << std::endl;
    while (counter < size && trig == 1)
    {
        namePrime[counter] = std::cin.get();
        if (namePrime[counter] == 10)
        {
            trig = 0;
            namePrime[counter] = '\0';
        }
        counter++;
    }
    debug("Name: " << namePrime);
    debug("name length " << strlen(namePrime));
    return;
}

