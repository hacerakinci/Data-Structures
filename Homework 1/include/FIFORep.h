/* @Author
Student Name: Hacer Yeter Akıncı 
Student ID : 150200007
Date: 10/27/2022
*/
#ifndef _FIFOREP
#define _FIFOREP

#include <iostream>
#include <stdio.h>
#include "ProcessRep.h"
class FIFORep 
{
private:
    ProcessRep* mpHead;
    ProcessRep* mpTail;
public:
    FIFORep();
    FIFORep(ProcessRep*);
    ~FIFORep();

    void setHead(ProcessRep*);
    ProcessRep* getHead();

    void setTail(ProcessRep*);
    ProcessRep* getTail();

    void queue(ProcessRep*);
    ProcessRep* dequeue();

    ProcessRep* searchID(int);
    void printFIFO();
};


#endif