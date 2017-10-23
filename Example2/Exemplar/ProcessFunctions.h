/* ProcessFunctions.h
 * Wyatt Emery
 * FEB 7 2017
 * COSC 4740 Project 2
 */

#include "QueueArray.h"

#ifndef PROCESS_FUNC_H
#define PROCESS_FUNC_H

#define PCB struct pcb


struct pcb
{
    int pid;
    int priority;
    int quantum; //keeps count of how long it has run with current priority will be reset each time it's pulled off
    int value; 
    int startTime;
    int runTime;
    int totalCPUTime;
    int turnaround; //I write in the turnaround time for the process as soon as it finishes. It was easy this way.
};

extern PCB* PCBInit(int Time);
    /* PCBInit takes only one parameter, the current time, in order to set the startTime of the process it's 
     * creating. It initializes all of the fields of the newly created struct to zero and returns pointer to the memory. 
     * The allocated memory should be deleted. */

extern void schedule(int& RunningState, PCB* runningProcess, QueueArray<int>& ReadyState, int Time);
    /* schedule makes all the scheduling decisions and decides when to take off a process and what process to put on the
     * processor. It performs the actual putting on and taking off of processes. it takes a reference to RunningState to
     * properly change it to the new running process. It takes a pointer to the currently running process so it can 
     * change priority and quantum of the process. It takes a refercne to ReadyState so it can pull off and put on 
     * processes. finally it takes a pass by value parameter time in order to calculate turnaround time for a process 
     * if need be. */

extern void incTime(int& Time, PCB* runningProcess);
    /* incTime increments time as well as increments the quantum and totalCPUTime of the currently running process. */

#endif

