/* @Author
Student Name: Hacer Yeter Akıncı 
Student ID : 150200007
Date: 10/27/2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    mpRunningProcess = NULL;
    mpProcessFIFO[0] = new FIFORep;
    mpProcessFIFO[1] = new FIFORep;
    mpProcessFIFO[2] = new FIFORep;
    pCpuObj = new CPURep();
    totalTime = 0;
    timeSliceCount = 0;
}
SchedulerRep::~SchedulerRep()
{
    delete mpProcessFIFO[0];
    delete mpProcessFIFO[1];
    delete mpProcessFIFO[2];
    delete pCpuObj; 
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{   
    return mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{  
    return mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    char type = p->getProcessType()[0];

    if (type == 'A'){
        mpProcessFIFO[0]->queue(p);
    }
    else if (type == 'B'){
        mpProcessFIFO[1]->queue(p);
    }
    else if(type == 'C'){
        mpProcessFIFO[2]->queue(p);
    }
}

ProcessRep* SchedulerRep::popProcess()
{
    if(mpRunningProcess != NULL && mpRunningProcess->remainingTime != 0){
        this->pushProcess(mpRunningProcess);
        mpRunningProcess = NULL;
    }

    if(mpProcessFIFO[0]->getHead() != NULL){
        return mpProcessFIFO[0]->dequeue();
    }
    else if(mpProcessFIFO[1]->getHead() != NULL){        
        return mpProcessFIFO[1]->dequeue();
    }
    else if(mpProcessFIFO[2]->getHead() != NULL){
        return mpProcessFIFO[2]->dequeue();
    }
    
    return NULL;

}

bool SchedulerRep::checkTimeSlice()
{   
    char type = mpRunningProcess->getProcessType()[0];

    if(type == 'A' && timeSliceCount == 2) return true;
    else if(type == 'B' && timeSliceCount == 4) return true;
    else if(type == 'C' && timeSliceCount == 8) return true;

    return false;
}

ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){

    if(p == NULL){
        mpRunningProcess = NULL;
        return NULL;
    }

    if(p == mpRunningProcess){
        timeSliceCount++;
    }
    else{
        timeSliceCount = 1;
    }

    mpRunningProcess = p;
    mpRunningProcess->setNext(NULL);

    if(pCpuObj->runCPU(mpRunningProcess, totalTime) == NULL){
        pCpuObj->getFinishedProcess()->queue(mpRunningProcess);
        mpRunningProcess = this->popProcess();
        timeSliceCount = 0;
    }
    
    return p;
    
}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{  
   ProcessRep* nextprocess = new ProcessRep(type, id ,arrivalTime, processTime);
   this->pushProcess(nextprocess);

    if(mpRunningProcess == NULL || 
      (mpRunningProcess != NULL && type[0] < mpRunningProcess->getProcessType()[0])){
        this->sendProcessToCPU(popProcess());
    }
    
    else if(checkTimeSlice()){
        this->sendProcessToCPU(popProcess());        
    }
    else{
        sendProcessToCPU(mpRunningProcess);
    }
    this->totalTime++;
}
void SchedulerRep::schedule(ProcessRep* p)
{ 
    if(p == NULL){
        if(mpRunningProcess == NULL || checkTimeSlice()){
            this->sendProcessToCPU(popProcess());
        }
        else{
            sendProcessToCPU(mpRunningProcess);
        }
    }
    this->totalTime++;
}
