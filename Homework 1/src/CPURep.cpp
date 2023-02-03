/* @Author
Student Name: Hacer Akıncı  
Student ID : 150200007
Date: 10/27/2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
   this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
   delete mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{ 
   if(p->startTime == -1){
      p->startTime = time;
   }

   p->remainingTime--;
   time++;
   
   if(p->remainingTime == 0){
      p->endTime = time;
      return NULL;
   }
   return p;
}

FIFORep* CPURep::getFinishedProcess()
{
   return mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
   mFinishedProcess = finishedProcess; 
}