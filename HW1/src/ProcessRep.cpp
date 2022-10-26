/* @Author
Student Name: Hacer Yeter Akıncı
Student ID : 150200007
Date: 
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{  
    mProcessType = processType;
    mProcessID = processID;
    mDeliverTime = deliverTime;
    mProcessTime = processTime;
    remainingTime = processTime;
    startTime = -1;
    endTime = -1;
    mpNext = NULL; 
}

ProcessRep::~ProcessRep()
{
}

ProcessRep* ProcessRep::getNext()
{
    if(mpNext !=NULL){
        return mpNext;
    }
    return NULL;
}

void ProcessRep::setNext(ProcessRep *next)
{   
    if(next == NULL){
        this->mpNext = NULL;
        return;
    }
    this->mpNext = next;
    this->mpNext->mpNext = NULL;
}

string ProcessRep::getProcessType()
{
    return mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    return mDeliverTime; 
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    return mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    mProcessID = processID;  
}

int ProcessRep::getProcessTime()
{
    return mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    mProcessTime = ProcessTime;
}