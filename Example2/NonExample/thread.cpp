//thread.c
//Wyatt Emery
//Shaya Wolf
//COSC 4010/5010 Fall 2017
//Original code borrowed from geeksforgeeks.org and modified by cybersecsy

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<iostream>
using namespace std;

// create a global variable to change it in threads
int nums[10] ={1,2,3,4,5,6,7,8,9,10}; 
char lets[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
// The function to be executed by all threads
void *myThread(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;
 
    if((*myid%2) == 0)
    {
      for(int i = 0; i < 1000; i++)
      {
        nums[i%10]++;
        lets[i%10]++;
      }
    }
    else
    {
      for(int i = 0; i < 1000; i++)
      {
        nums[i%10]--;
        lets[i%10]--;
      }
    }
 
}
 
int main()
{
 
    /*Create all threads*/

    cout << "Int Array start = {";
    for(int i = 0; i < 10; i++)
    {
      cout << nums[i] << ",";
    }
    cout << "}" << endl;
    
    cout << "Char Array start = {";
      for(int i = 0; i < 10; i++)
      {
        cout << lets[i] << ",";
      }
      cout << "}" << endl;
    
    int numThreads = 10;
    int tIds[10] = {0,1,2,3,4,5,6,7,8,9}; 
    pthread_t threadIDs[numThreads];
    for(int i = 0; i < numThreads; i++)
    {
      if(pthread_create(&threadIDs[i], NULL, myThread, (void*)&tIds[i])!= 0)
      {
        perror("error creating thread");
        exit(1);
      }
    }
    
    //wait for threads to finish
    for(int i = 0; i < numThreads; i++)
    {
      pthread_join(threadIDs[i], NULL);
    }  
    
    cout << "Int Array End = {";
    for(int i = 0; i < 10; i++)
    {
      cout << nums[i] << ",";
    }
    cout << "}" << endl;
    
    cout << "Char Array End = {";
      for(int i = 0; i < 10; i++)
      {
        cout << lets[i] << ",";
      }
      cout << "}" << endl;
    return 0;
}
