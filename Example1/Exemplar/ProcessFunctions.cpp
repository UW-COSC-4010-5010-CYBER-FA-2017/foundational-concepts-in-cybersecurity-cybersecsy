/* ProcessFunctions.cpp
 * Wyatt Emery
 * FEB 7 2017
 * COSC 4740 Project 2
 */

#define PCB struct pcb


#include"ProcessFunctions.h"
#include <cstddef>

PCB* PCBInit(int Time)
{
    PCB* ret = new PCB;
    ret -> pid = 0; //no change
    ret -> priority = 0;
    ret -> quantum = 0; //keeps count of how long it has run with current priority will be reset each time it's pulled off
    ret -> value = 0; 
    ret -> startTime = Time; //no change
    ret -> runTime = 0;//no change
    ret -> totalCPUTime = 0; 
    ret -> turnaround = -1;
    
    return ret;

}

void schedule(int& RunningState, PCB* runningProcess, QueueArray<int>& ReadyState, int Time)
{
    if(RunningState != -1) /*If there is a process on the processor*/
    {
        /* Calculate the fullQuantum based on priority of that process. I did this because I didn't want to import the 
         * math library. */
        int fullQuantum = 1;
        switch(runningProcess->priority)
        {
            case 0:
                break;
            case 1:
                fullQuantum = 2;
                break;
            case 2:
                fullQuantum = 4;
                break;
            default: 
                fullQuantum = 8;
                break;
        }
         
        /*If the running process has completed pull it off and Calculate turnaround time */ 
        if(runningProcess->totalCPUTime == runningProcess->runTime)
        {
            runningProcess->priority = 0;
            RunningState = -1;
            runningProcess->turnaround = Time - runningProcess->startTime;
        }
        else if(runningProcess->quantum == fullQuantum)
        {
            /*Else if the process has run for a full, quantum pull it off. and decrease its priority. set its quantum to 
             * 0 and put it back on the ready queue.*/
            if(runningProcess->priority < 3)
                runningProcess->priority++;
            runningProcess->quantum = 0;
            int ret = ReadyState.Enqueue(RunningState, runningProcess->priority);
            if(ret == -1) cerr << "QueueArray Error: out of bounds" << endl;
            if (ret == 0) cerr << "QueueArray Error: unknown Error" << endl;
            RunningState = -1;
        }
    }
    /* If there is no running process, select the next process and put it on the processor. */
    if(RunningState == -1)
    {
        if(ReadyState.QAsize() != 0)
            RunningState = ReadyState.Dequeue();
        else RunningState = -1;
    }
}

void incTime(int& Time, PCB* runningProcess)
{
    Time++;
    if(runningProcess != NULL)
    {
        runningProcess->quantum++;
        runningProcess->totalCPUTime++;
    }
}