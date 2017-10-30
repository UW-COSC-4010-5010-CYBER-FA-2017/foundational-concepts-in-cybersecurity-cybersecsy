/* Commander.cpp
 * Wyatt Emery
 * FEB 7 2017
 * COSC 4740 Project 
 * 
 * Commander forks and starts ProcessManager and then passes all input to ProcessManager. Before passing input on, 
 * commander will parse and validate all input. the only characters written to the pipe are single characters that are 
 * the commands. All the parameters are written as their respective data types usually integer. However, command C has a
 * character parameter. This prevents a bunch of sprintf's and a bunch of atoi's on the other end. I chose to not use 
 * any strings and just used char*, because strings were causing me trouble and the c getline function works very well. 
 * I do free the data allocated by getline to avoid memory leaks.
 */



#include<iostream>
#include<unistd.h> //fork, exec,
#include<cstdlib>
#include<stdio.h>//perror
#include <sys/types.h> //wait
#include <sys/wait.h>
#include<string.h>
#include<string>

using namespace std;

#define ReadEnd 0
#define WriteEnd 1


void cleanUp(int* ProcessManagerPipe, pid_t childPID, char* lineptr);
    /* This function simply closes ProcessManagerPipe on the write end, waits on its child and free's lineptr in case of 
     * an early termination. */

int main(int argc, char** argv)
{
    int ret;
    int ProcessManagerPipe[2];
    ret = pipe(ProcessManagerPipe);
    if(ret != 0) perror("Commander: pipe() Error");
        
    pid_t childPID = fork();
    if(childPID == -1)
    {
        perror("Commander: fork() Error");
        
        ret = close(ProcessManagerPipe[WriteEnd]);
        if(ret != 0) perror("Commander: close() Error");
        ret = close(ProcessManagerPipe[ReadEnd]);
        if(ret != 0) perror("Commander: close() Error");
        
        exit(1);
    }
    /******************************************************************************************************************/
    if(childPID == 0) //Child
    {
        char ProcessManagerPipe_0[10];
        char ProcessManagerPipe_1[10];
        sprintf(ProcessManagerPipe_0, "%d", ProcessManagerPipe[0]);
        sprintf(ProcessManagerPipe_1, "%d", ProcessManagerPipe[1]);
        
        execl("./processManager", "./processManager", ProcessManagerPipe_0, ProcessManagerPipe_1, NULL);
        cerr << "Commander: execl() Error" << endl;
    
        ret = close(ProcessManagerPipe[WriteEnd]);
        if(ret != 0) perror("Commander: close() Error");
        ret = close(ProcessManagerPipe[ReadEnd]);
        if(ret != 0) perror("Commander: close() Error");
        
        exit(1);
    }
    /******************************************************************************************************************/
    else //parent
    {
        ret = close(ProcessManagerPipe[0]);
        if(ret != 0) perror("Commander: close() Error");
        
        /*Read input from stdin, parse, validate and pass to ProcessManager*/
        char delim[2] = " ";
        char* lineptr = NULL;
        size_t n = 0;
        
        /* Read in line at a time */
        while((getline(&lineptr, &n, stdin) != -1))
        {
            /*Sleep 2 seconds*/
            sleep(2);
            char* token;
            
            if(strlen(lineptr) == 2) token = strtok(lineptr, "\n");
            else token = strtok(lineptr, delim);
            
            /* If first letter is not a single letter command, its already wrong */
            if(strlen(token) != 1) cerr << "Invalid Command" << endl;
            else
            {
                switch(token[0]) //Switch on first letter
                {
                    case('S'):
                    {
                        int params[3];
                        bool good = true;
                        int i = 0;
                        /* Pull out integer parameters. */
                        while((i < 3) && (good))
                        {
                            token = strtok(NULL, delim);
                            if(token == NULL) 
                            {
                                cerr << "Usage: S PID VALUE RUN_TIME" << endl;
                                good = false;
                            }
                            else params[i] = atoi(token);
                            if(params[i] < 0)
                            {
                                cerr << "All parameters must be nonnegative" << endl;
                                good = false;
                            }
                            i++;
                        }
                        if(!good) break;
                        
                        if(params[2] == 0)
                        {
                            cerr << "Run_Time must be > 0" << endl;
                            break;
                            
                        }
                        /**********************************************************************************************/
                        
                        /* Only continue with validated input */
                        /* Write out the cmd followed by the integer parameters */
                        char cmd = 'S';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        for(int i = 0; i < 3; i++)
                        {
                            ret = write(ProcessManagerPipe[WriteEnd], (void*) &params[i], sizeof(int));
                            if(ret == -1) 
                            {
                                perror("Commander: write() Error");
                                cleanUp(ProcessManagerPipe, childPID, lineptr);
                                exit(1);
                            }
                        }
                        
                        break;
                    }
                    case('B'):
                    {
                        int rid;
                        
                        token = strtok(NULL, delim);
                        if(token == NULL) 
                        {
                            cerr << "Usage: U RID" << endl;
                            break;
                        }
                        
                        rid = atoi(token);
                        if((rid < 0) || (rid > 2))
                        {
                            cerr << "rid must be an integer between 0 and 2 inclusive"; 
                            cerr << endl;
                            break;
                        }
                        
                        /* Write out cmd and rid */
                        char cmd = 'B';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &rid, sizeof(int));                        
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        
                        break;
                    }
                    case('U'):
                    {
                        int rid;
                        
                        token = strtok(NULL, delim);
                        if(token == NULL) 
                        {
                            cerr << "Usage: U RID" << endl;
                            break;
                        }
                        
                        rid = atoi(token);
                        if((rid < 0) || (rid > 2))
                        {
                            cerr << "rid must be an integer between 0 and 2 inclusive"; 
                            cerr << endl;
                            break;
                        }
                        
                        /* Write out cmd and rid */
                        
                        char cmd = 'U';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &rid, sizeof(int));                        
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        
                        break;
                    }
                    case('Q'):
                    {
                        char cmd = 'Q';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        break;
                    }
                    case('C'):
                    {
                        /* Get and validate parameter and number */
                        
                        char param;
                        int num;
                        
                        token = strtok(NULL, delim);
                        if((token == NULL) || (strlen(token) != 1)) 
                        {
                            cerr << "Usage: C CMD NUM" << endl;
                            break;
                        }
                        param = token[0];
                        if(!((param == 'A') || (param == 'S') || (param == 'M') || (param == 'D')))
                        {
                            cerr << "Usage: C CMD NUM : Unrecognized CMD!" << endl;
                            break;
                        }
                        token = strtok(NULL, delim);
                        if(token == NULL) 
                        {
                            cerr << "Usage: C CMD NUM" << endl;
                            break;
                        }
                        num = atoi(token);
                        
                        if(num < 0)
                        {
                            cerr << "Usage: C CMD NUM: " << "NUM must be positive! " << endl;
                            break;
                        }
                        
                        /**********************************************************************************************/
                        /* Write out cmd, parameter and number */
                        char cmd = 'C';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &param, sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &num, sizeof(int));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        
                        break;
                    }
                    case('P'):
                    {
                        char cmd = 'P';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        break;
                    }
                    case('T'):
                    {
                        char cmd = 'T';
                        ret = write(ProcessManagerPipe[WriteEnd], (void*) &cmd , sizeof(char));
                        if(ret == -1) 
                        {
                            perror("Commander: write() Error");
                            cleanUp(ProcessManagerPipe, childPID, lineptr);
                            exit(1);
                        }
                        
                        /* When T is ecountered just clean up and exit here */
                        cleanUp(ProcessManagerPipe, childPID, lineptr);
                        return 0;
                    }
                    default:
                    {
                        cerr << "Invalid Command" << endl;
                        break;
                    }
                }
            }
            /* free lineptr and set it to NULL before calling getline again */
            free(lineptr);
            lineptr = NULL;
            n = 0;
        }
        
        ret = close(ProcessManagerPipe[WriteEnd]);
        if(ret != 0) perror("Commander: close() Error");
        
        /*Wait on ProcessManager*/
        ret = waitpid(childPID, NULL, 0);
        if(ret == -1) perror("Commander: wait() Error");
    }
    
    return 0;
}

void cleanUp(int* ProcessManagerPipe, pid_t childPID, char* lineptr)
{
    int ret;
    
    free(lineptr);
    
    ret = close(ProcessManagerPipe[WriteEnd]);
    if(ret != 0) perror("Commander: close() Error");
    
    /*Wait on ProcessManager*/
    ret = waitpid(childPID, NULL, 0);
    if(ret == -1) perror("Commander: wait() Error");
}
