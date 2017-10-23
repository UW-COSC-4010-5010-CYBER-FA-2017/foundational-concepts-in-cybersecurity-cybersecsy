/* Reporter.cpp
 * Wyatt Emery
 * FEB 7 2017
 * COSC 4740 Project 2
 * 
 * Reporter is executed by Processmanager in order to handle the printing off the state of the scheduler. When printing 
 * off BlockedState and ready state, the first thing read in is the number of processes. then reporter loops based on 
 * that number until it has printed out all processes associated with a state.
 */


#include <iostream>
#include <unistd.h>
#include "ProcessFunctions.h"
#include<stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

#define PCB struct pcb
#define ReadEnd 0
#define WriteEnd 1

void cleanUp(int* pipe, PCB* table);

int main(int argc, char** argv)
{
    
    int ret;
    /*Get Pipe fd's from argv*/
    int ProcessManagerPipe[2];
    ProcessManagerPipe[ReadEnd] = atoi(argv[1]);
    ProcessManagerPipe[WriteEnd] = atoi(argv[2]);
    ret = close(ProcessManagerPipe[WriteEnd]);
    if(ret != 0) perror("Reporter: close() Error");
    
    
    /******************************************************************************************************************/
    int count = 53;
    
    string format = "%2d%5d%13d%9d%14d\n";
    string processFormat= "PID  Priority  Value  Start Time  Total CPU time\n";
    
    printf("%s\n",string(count,'*').c_str());
    cout << "The current system state is as follows:" << endl;
    printf("%s\n\n",string(count,'*').c_str());
    
    
    /* Read in Time */
    int Time;
    ret = read(ProcessManagerPipe[ReadEnd], (int*) &Time, sizeof(int));
    if(ret == -1)
    {
        perror("Reporter: read() Error");
        cleanUp(ProcessManagerPipe, NULL);
        exit(1);
    }
    
    /* Print out Current Time*/
    cout << "CURRENT TIME: " << Time << endl;
    cout << endl;
    
    /* Read in RunningState */
    int RunningState;
    ret = read(ProcessManagerPipe[ReadEnd], (int*) &RunningState, sizeof(int));
    if(ret == -1)
    {
        perror("Reporter: read() Error");
        cleanUp(ProcessManagerPipe, NULL);
        exit(1);
    }
    
    if(RunningState == -1) cout << "RUNNING PROCESS: No Running Process" << endl << endl;
    else
    {
        /* Read in RunningProcess */
        PCB* runningProcess = new PCB;
        ret = read(ProcessManagerPipe[ReadEnd], (PCB*) runningProcess, sizeof(PCB));
        if(ret == -1)
        {
            perror("Reporter: read() Error");
            cleanUp(ProcessManagerPipe, runningProcess);
            exit(1);
        }
        
        
        /*Print out Running Process*/
        cout << "RUNNING PROCESS:" << endl;
        cout << processFormat;
        printf(format.c_str(), runningProcess->pid, runningProcess->priority, runningProcess->value, runningProcess->startTime, 
               runningProcess->totalCPUTime);
        delete runningProcess;
        
    }
    cout << endl;
    /******************************************************************************************************************/
    /* Print out Blocked Processes */
    cout << "BLOCKED PROCESSES:" << endl;
    
    PCB* currentTable = new PCB;
    
    for(int i = 0; i < 3; i++)
    {   

        int numProcesses = 0;
        /* Read in number of processes */
        ret = read(ProcessManagerPipe[ReadEnd], (int*) &numProcesses, sizeof(int));
        if(ret == -1)
        {
            perror("Reporter: read() Error");
            cleanUp(ProcessManagerPipe, currentTable);
            exit(1);
        }
        
        cout << "Queue of processes blocked for resource " << i;
        
        if(numProcesses > 0)
        {
            cout << " : " << endl;
            cout << processFormat;
        }
        else cout << " is empty" << endl;
        
        for(int k = 0; k < numProcesses; k++)
        {
            /*Read in Table*/
            ret = read(ProcessManagerPipe[ReadEnd], (PCB*) currentTable, sizeof(PCB));
            if(ret == -1)
            {
                perror("Reporter: read() Error");
                cleanUp(ProcessManagerPipe, currentTable);
                exit(1);
            }
            /*Print out Table*/
            printf(format.c_str(), currentTable->pid, currentTable->priority, currentTable->value, currentTable->startTime, 
                   currentTable->totalCPUTime);
        }
        
    }
    cout << endl;
    /******************************************************************************************************************/
    /* Print out ReadyState */
    
    cout << "PROCESSES READY TO EXECUTE:" << endl;
    int numProcesses = 0;
    /* Read in number of processes for each priority*/
    for(int i = 0; i < 4; i++)
    {
        ret = read(ProcessManagerPipe[ReadEnd], (int*) &numProcesses, sizeof(int));
        if(ret == -1)
        {
            perror("Reporter: read() Error");
            cleanUp(ProcessManagerPipe, currentTable);
            exit(1);
        }
        
        cout << "Queue of processes with priority " << i;
        if(numProcesses > 0)
        {
            cout << " : " << endl;
            cout << processFormat;
        }
        else printf(" is empty\n");
        
        for(int j = 0; j < numProcesses; j++)
        {
            /*Read in Table*/
            ret = read(ProcessManagerPipe[ReadEnd], (PCB*) currentTable, sizeof(PCB));
            if(ret == -1)
            {
                perror("Reporter: read() Error");
                cleanUp(ProcessManagerPipe, currentTable);
                exit(1);
            }
            
            /*Print out Table*/
            printf(format.c_str(), currentTable->pid, currentTable->priority, currentTable->value, currentTable->startTime, 
                   currentTable->totalCPUTime);
        }
    }
    
    printf("%s\n\n",string(count,'*').c_str());
    
    /******************************************************************************************************************/
    
    
    ret = close(ProcessManagerPipe[ReadEnd]);
    if(ret != 0) perror("Reporter: close() Error");
    
    
    delete currentTable;
    
    return 0;
}

void cleanUp(int* pipe, PCB* table)
{
    int ret;
    ret = close(pipe[ReadEnd]);
    if(ret == -1) perror("Reporter: close() Error");
    if(table!= NULL) delete table;
}