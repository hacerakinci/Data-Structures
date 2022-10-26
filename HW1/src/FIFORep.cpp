/* @Author
Student Name: Hacer Yeter Akıncı 
Student ID : 150200007
Date: 
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    mpHead = NULL;
    mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    mpHead = head;
    mpTail = NULL;
}


FIFORep::~FIFORep()
{
   /*ProcessRep* node = mpHead;
   ProcessRep* temp;
    while(node != NULL){
        temp = node->getNext();
        delete(node);
        node = temp;
    } */
}

void FIFORep::setHead(ProcessRep* head)
{
    if(mpHead == NULL){
        mpHead = head;
        mpTail = NULL;
    }
    else{
        head->setNext(mpHead);
        mpHead = head;        
    }
}

ProcessRep* FIFORep::getHead()
{
    return mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
   if(mpTail == NULL){
        mpHead->setNext(tail);
    }
    else{
        mpTail->setNext(tail);    
    }
    mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    return mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    /*
        The function add a process to the tail of the queue.
    */
    if(mpHead == NULL){
        this->setHead(p);
    }
    else {
        this->setTail(p);
    }
    
}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function removes a process from the HEAD of the FIFO and returns it. If there is no item, it returns NULL
    */   
   if(mpHead == NULL){
        return NULL;
   }
   else{
        ProcessRep* temp = mpHead;
        mpHead = mpHead->getNext();
        return temp;
   }
} 

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        search the list for a given process ID.
    */ 
    /*
        YOUR CODE HEAR
    */
    ProcessRep* node = mpHead;
    while(node != NULL){
        if(node->getProcessID() == id){
            return node;
        }
        else{
            node = node->getNext();
        }
    }
    return NULL;
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to tail.
    */
    /*
        YOUR CODE HEAR
    */

    ProcessRep* node = mpHead;
    while(node != NULL){
        cout<< node->getProcessType() << node->getProcessID() << " " << node->startTime << " " << node->endTime <<" ";
        node = node->getNext();
    }
}