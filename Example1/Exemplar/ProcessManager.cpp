/* ProcessManager.cpp
 * Wyatt Emery
 * FEB 7 2017
 * COSC 4740 Project 2
 * 
 * ProcessManager reads in commands from the pipe from commander. It is looped to read a single character at a time with
 * knowledge that the character will be a valid command. Because the commander only writes to the pipe valid and 
 * complete commands, very little error checking on input is done here. Only checks on read(). In each command case 
 * ProcessManager reads in exactly the number of parameters, usually integers, as such. PcbTable is a vector of 
 * PCB* that each process is put on to when it is created. At the end, all the PCB's are properly deleted. 
 * NOTE: I use the c function atoi() for conversions of input to integer parameters. Letters passed to atoi() often 
 * come back as 0 and as such are considered valid input and the commande will be run with 0 as an integer parameter.
 */

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<vector>
#include "QueueArray.hpp"
#include "ProcessFunctions.h"
#include<cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include<cstdlib>
#include <string>



using namespace std;


#define ReadEnd 0
#define WriteEnd 1
#define PCB struct pcb

void cleanUp(vector<PCB*>& PcbTable, int* pipe, QueueArray<int>** BlockedProcesses);

int main(int argc, char** argv)
{
    int RunningState = -1; //Index of currently running process
    vector<PCB*> PcbTable;
    int Time = 0;
    QueueArray<int> ReadyState(4); //4 queues corresponding to priorities
    QueueArray<int>* BlockedProcesses[3];

    BlockedProcesses[0] = new QueueArray<int>(4);
    BlockedProcesses[1] = new QueueArray<int>(4);
    BlockedProcesses[2] = new QueueArray<int>(4);
/**********************************************************************************************************************/

    int ret;
    /*Get Pipe fd's from argv*/
    int CommanderPipe[2];
    CommanderPipe[ReadEnd] = atoi(argv[1]);
    CommanderPipe[WriteEnd] = atoi(argv[2]);
    ret = close(CommanderPipe[WriteEnd]);
    if(ret != 0) perror("ProcessManager: close() Error");
    
    /* Read in input from pipes*/
    char buf = '\0';
    int numread;
    
    /* Read only a single character because I know that is what's coming down the pipe. that character is the current 
     * command. */
    while((numread = read(CommanderPipe[ReadEnd], &buf, sizeof(char))) > 0)
    {
        switch(buf)
        {
            case('S'):
            {
                
                /*Read in pid, value, and runtime*/
                int pid;
                int value;
                int runTime;
                
                ret = read(CommanderPipe[ReadEnd], (int*) &pid, sizeof(int));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                ret = read(CommanderPipe[ReadEnd], (int*) &value, sizeof(int));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                ret = read(CommanderPipe[ReadEnd], (int*) &runTime, sizeof(int));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                /******************************************************************************************************/
                PCB* newProcess = PCBInit(Time);
                
                newProcess->pid = pid;
                newProcess->value = value;
                newProcess->runTime = runTime;
                
                /*Add new Process to PcbTable */
                PcbTable.push_back(newProcess);
                int index = PcbTable.size() - 1;
                
                /*Add new process index to readyState with priority 0*/
                ret = ReadyState.Enqueue(index, 0);
                if(ret == -1) cerr << "QueueArray Error: Out of bounds" << endl;
                else if (ret == 0) cerr << "QueueArray Error: unknown Error" << endl;
                
                /*Set startTime*/
                newProcess->startTime = Time;
                /* Run scheduler to potentially put this process on the processor if there is not currently running 
                 * process. */
                if(RunningState == -1) schedule(RunningState, NULL, ReadyState, Time);
                
                break;
            }
            case('B'):
            {
                /* Read in rid */
                int rid;
                ret = read(CommanderPipe[ReadEnd], (int*) &rid, sizeof(int));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                if(RunningState == -1)
                {
                    cerr << "B: No currently running Process" << endl;
                    break;
                }

                /* increase priority by 1 */
                if(PcbTable[RunningState]->priority > 0)
                    PcbTable[RunningState]->priority--;
                
                /* reset quantum */
                PcbTable[RunningState]-> quantum = 0;
                
                /* add it to block state for correct resource and priority */
                ret = BlockedProcesses[rid]->Enqueue(RunningState, PcbTable[RunningState]->priority);
                if(ret == -1) cerr << "QueueArray Error: Out of bounds" << endl;
                else if (ret == 0) cerr << "QueueArray Error: unknown Error" << endl;
                
                /* stop currently running process */
                RunningState = -1;
                
                /* run scheduling algorithm, NULL because there is always no currently running process after a B cmd */
                schedule(RunningState, NULL, ReadyState, Time);
                
                break;
            }
            case('U'):
            {
                /* Read in rid */
                int rid;
                ret = read(CommanderPipe[ReadEnd], (int*) &rid, sizeof(int));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                /* Dequeue process from rid Queue*/
                int index;
                if(BlockedProcesses[rid]->QAsize() == 0)
                { 
                    cerr << "U: No blocked processes" << endl;
                    break;
                }
                index = BlockedProcesses[rid]->Dequeue();
                
                /* Add that process to ready queue then run scheduler only if there is not process currently running */
                ret = ReadyState.Enqueue(index, PcbTable[index]->priority);
                if(ret == -1) cerr << "QueueArray Error: Out of bounds" << endl;
                else if (ret == 0) cerr << "QueueArray Error: unknown Error" << endl;
                
                /* Only run schedule() if there is no running process as this unblocked process might need to jump on 
                 * the processor. */
                if(RunningState == -1) schedule(RunningState, NULL, ReadyState, Time);
                
                break;
            }
            case('C'):
            {
                
                /*Read in Param and num*/
                char param;
                int num;
                ret = read(CommanderPipe[ReadEnd], (char*) &param, sizeof(char));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                ret = read(CommanderPipe[ReadEnd], (int*) &num, sizeof(int));
                if(ret == -1 )
                {
                    perror("ProcessManager Error: read()");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                
                /* If there is not running process, there is no operation to be done on it. */
                
                if(RunningState == -1)
                {
                    cerr << "C: No currently running Process" << endl;
                    break;
                }
                
                /* Execute given command with num */
                switch(param)
                {
                    case('A'):
                        PcbTable[RunningState]->value+=num;
                        break;
                    case('S'):
                        PcbTable[RunningState]->value-=num;
                        break;
                    case('M'):
                        PcbTable[RunningState]->value*=num;
                        break;
                    case('D'):
                        PcbTable[RunningState]->value/=num;
                        break;
                    default:
                        break;
                }
                /* Drop through*/
            }
            case('Q'):
            {
                if(RunningState == -1)
                {
                    incTime(Time, NULL);
                    schedule(RunningState, NULL, ReadyState, Time);
                }
                else
                {
                    incTime(Time, PcbTable[RunningState]);
                    schedule(RunningState, PcbTable[RunningState], ReadyState, Time);
                }
                break;
            }
            case('P'):
            {                
                /* Set up Pipe and Fork*/
                int ReporterPipe[2];
                ret = pipe(ReporterPipe);
                if(ret != 0)
                {
                    perror("ProcessManager: pipe() Error");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    ret = close(ReporterPipe[WriteEnd]);
                    if(ret == -1) perror("ProcessManager: close() Error");
                    ret = close(ReporterPipe[ReadEnd]);
                    if(ret == -1) perror("ProcessManager: close() Error");
                    
                    exit(1);
                }
                
                pid_t childPID = fork();
                if(childPID == -1)
                {
                    perror("ProcessManager: fork() Error!");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    ret = close(ReporterPipe[WriteEnd]);
                    if(ret == -1) perror("ProcessManager: close() Error");
                    ret = close(ReporterPipe[ReadEnd]);
                    if(ret == -1) perror("ProcessManager: close() Error");
                    exit(1);
                }
                /******************************************************************************************************/
                
                if(childPID == 0) //Child
                {
                    /* Just set up pipes and execute reporter, passing the pipes as input. */
                    char ReporterPipeRead[10];
                    char ReporterPipeWrite[10];
                    sprintf(ReporterPipeRead, "%d", ReporterPipe[ReadEnd]);
                    sprintf(ReporterPipeWrite, "%d", ReporterPipe[WriteEnd]);
                    
                    execl("./reporter", "./reporter", ReporterPipeRead, ReporterPipeWrite, NULL);
                    cerr << "ProcessManager: execl() Error" << endl;
                    
                    ret = close(ReporterPipe[WriteEnd]);
                    if(ret == -1) perror("ProcessManager: close() Error");
                    ret = close(ReporterPipe[ReadEnd]);
                    if(ret == -1) perror("ProcessManager: close() Error");
                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                    exit(1);
                }
                else //parent
                {
                    ret = close(ReporterPipe[ReadEnd]);
                    if(ret != 0) perror("ProcessManager: close() Error");
                    
                    /**************************************************************************************************/
                    
                    /* write time to pipe */
                    ret = write(ReporterPipe[WriteEnd], (void*) &Time, sizeof(int));
                    if(ret == -1) 
                    {
                        perror("ProcessManager: write() Error");
                        cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                        ret = close(ReporterPipe[WriteEnd]);
                        if(ret == -1) perror("ProcessManager: close() Error");
                        ret = waitpid(childPID, NULL, 0);
                        if(ret == -1) perror("ProcessManager: waitpid() Error");
                        
                        exit(1);
                    }
                        
                    
                    /* Write runningState to pipe*/
                    ret = write(ReporterPipe[WriteEnd], (void*) &RunningState, sizeof(int));
                    if(ret == -1) 
                    {
                        perror("ProcessManager: write() Error");
                        cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                        ret = close(ReporterPipe[WriteEnd]);
                        if(ret == -1) perror("ProcessManager: close() Error");
                        ret = waitpid(childPID, NULL, 0);
                        if(ret == -1) perror("ProcessManager: waitpid() Error");
                        
                        exit(1);
                    }
                    
                    /* write running process to pipe */
                    if(RunningState != -1)
                    {
                        ret = write(ReporterPipe[WriteEnd], (void*)PcbTable[RunningState], sizeof(PCB));
                        if(ret == -1) 
                        {
                            perror("ProcessManager: write() Error");
                            cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                            ret = close(ReporterPipe[WriteEnd]);
                            if(ret == -1) perror("ProcessManager: close() Error");
                            ret = waitpid(childPID, NULL, 0);
                            if(ret == -1) perror("ProcessManager: waitpid() Error");
                            
                            exit(1);
                        }
                    }

                    /**************************************************************************************************/
                    
                    /* Write out all processes in BlockedProcesses. I stepped through each QueueArray in 
                     * BlockedProcesses and in each one, the first thing I do is write out the number of processes in 
                     * that resource. I do this to let Reporter know how much stuff is coming. Next, for each Queue in 
                     * the QueueArray (priority) I write out all the processes in that Queue. I pass the PCB* struct 
                     * casted as a void* and casted back to PCB* on the other side. */
                    for(int i = 0; i < 3; i++)
                    {
                        
                        /* Write out number of processes in this resource*/
                        int numProcesses = BlockedProcesses[i]->QAsize();

                        ret = write(ReporterPipe[WriteEnd], (void*) &numProcesses, sizeof(int));
                        if(ret == -1) 
                        {
                            perror("ProcessManager: write() Error");
                            cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                            ret = close(ReporterPipe[WriteEnd]);
                            if(ret == -1) perror("ProcessManager: close() Error");
                            ret = waitpid(childPID, NULL, 0);
                            if(ret == -1) perror("ProcessManager: waitpid() Error");
                            
                            exit(1);
                        }
                        
                        for(int k = 0; k < 4; k++)
                        {                            
                            int* state = BlockedProcesses[i]->Qstate(k);
                            if(state == NULL) cerr << "QueueArray Error: out of bounds" << endl;
                            
                            
                            for(int j = 0; j < BlockedProcesses[i]->Qsize(k); j++)
                            {
                                /* Write out each PCB in this queue*/
                                ret = write(ReporterPipe[WriteEnd],(void*) PcbTable[state[j]], sizeof(PCB));
                                if(ret == -1) 
                                {
                                    perror("ProcessManager: write() Error");
                                    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                                    delete[] state;
                                    state = NULL;
                                    ret = close(ReporterPipe[WriteEnd]);
                                    if(ret == -1) perror("ProcessManager: close() Error");
                                    ret = waitpid(childPID, NULL, 0);
                                    if(ret == -1) perror("ProcessManager: waitpid() Error");
                                    
                                    exit(1);
                                }
                            }
                            delete[] state;
                            state = NULL;
                        }
                    }

                    /**************************************************************************************************/
                    
                    
                    /* Write out all Processes in ReadyState. For each queue in ready state: First off I write out the 
                     * number of processes in that queue. Then I write out all the processes in that queue. This is done
                     * similarly to writing out the BlockedProcesses. */
                    for(int i = 0; i < 4; i++)
                    {
                        /* Write out number of processes in each queue */
                        int numProcesses = ReadyState.Qsize(i);
                        
                        ret = write(ReporterPipe[WriteEnd], (void*) &numProcesses, sizeof(int));                        
                        if(ret == -1) 
                        {
                            perror("ProcessManager: write() Error");
                            ret = close(ReporterPipe[WriteEnd]);
                            if(ret == -1) perror("ProcessManager: close() Error");
                            cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                            ret = waitpid(childPID, NULL, 0);
                            if(ret == -1) perror("ProcessManager: waitpid() Error");
                            
                            exit(1);
                        }
                        /* Write out each process in each queue*/
                        int* state = ReadyState.Qstate(i);
                        if(state == NULL) cerr << "QueueArray Error: out of bounds" << endl;
                        
                        for(int k = 0; k < numProcesses; k++)
                        {
                            ret = write(ReporterPipe[WriteEnd], (void*) PcbTable[state[k]], sizeof(PCB));                                                        
                            if(ret == -1) 
                            {
                                perror("ProcessManager: write() Error");
                                ret = close(ReporterPipe[WriteEnd]);
                                if(ret == -1) perror("ProcessManager: close() Error");
                                
                                delete[] state;
                                state = NULL;
                                cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                                
                                ret = waitpid(childPID, NULL, 0);
                                if(ret == -1) perror("ProcessManager: waitpid() Error");

                                exit(1);
                            }
                        }
                        delete[] state;
                        state = NULL;
                    }

                    /**************************************************************************************************/

                    
                    ret = close(ReporterPipe[WriteEnd]);
                    if(ret != 0) perror("ProcessManager: close() Error");
                                        
                    /*Wait on Reporter*/
                    ret = waitpid(childPID, NULL, 0);
                    if(ret == -1)
                    {
                        perror("ProcessManager: waitpid() Error");
                        cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                        exit(1);
                    }
                }
                break;
            }
            case('T'):
            {
                /* Calculate Average Turnaround time and print it out */
                
                int count = 0;
                int total = 0;
                for(unsigned int i = 0; i < PcbTable.size(); i++)
                {
                    if(PcbTable[i]->turnaround != -1) 
                    {
                        total+= PcbTable[i]->turnaround;
                        count++;
                    }
                    
                }
                double average = (double) total/count;
                printf("The Average Turnaround Time: %7.4f\n", average);
                cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
                return 0;
                break;
            }
            default:
                cerr << "ProcessManager: Unknown Error" << endl;
        }
    }
    
    if(numread == -1)
    {
        perror("ProcessManager: read() Error");
        cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
        exit(1);
    }
    
    cleanUp(PcbTable, CommanderPipe, BlockedProcesses);
    
    return 0;
}

void cleanUp(vector<PCB*>& PcbTable, int* pipe, QueueArray<int>** BlockedProcesses)
{
    for(unsigned int i = 0; i < PcbTable.size(); i++)
    {
        delete PcbTable[i];
    }
    int ret = close(pipe[ReadEnd]);
    if(ret == -1) perror("ProcessManager: close() Error");
    delete BlockedProcesses[0];
    delete BlockedProcesses[1];
    delete BlockedProcesses[2];
}



