//QueueArray.cpp
//Wyatt Emery
//1-24-17
//COSC 4740 Project 1

#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H

#include <cstdlib>  //This is for the exit command.
#include <queue>
#include<iostream>

using namespace std;


template <class T>
class QueueArray
{
public:
    QueueArray(int sz = 10);
    ~QueueArray();
    int Asize() const; 
    int QAsize() const; 
    int Qsize(int index) const;
    
    T Dequeue();
    int Enqueue(const T &item,const int index);
    T* Qstate(int index);
    
private:
    int _size;      //size of the array
    queue<T>* _array;   //the array of queues
    int _totalItems; //total number of items stored in the queues
};


//Constructor for the queue array.  It sets the default size
//to 10, initializes the private variables size and totalItems
template <typename T>
QueueArray<T>::QueueArray(int sz) : _size(sz), _totalItems(0)
{
    _array = new queue<T>[_size];
    if( _array == NULL)
    {
        cout << "Not enough memory to create the array" << endl;
        exit(-1);
    }
}

template <typename T>
QueueArray<T>::~QueueArray()
{
    /* The only memory that is dynamically allocated is _array and here it is 
     * freed*/
    delete[] _array;
}

template <typename T>
int QueueArray<T>::Enqueue(const T &item,const int index)
{
    //if index is out of range return -1
    if((index < 0) || (index > _size - 1))
        return -1;
    
    size_t temp = _array[index].size();
    _array[index].push(item);
    
    /* size did not increase and therefore the item was not successfully pushed 
     * onto the queue, unkown error*/
    if(_array[index].size() != (temp + 1))
        return 0;
    
    //Item was successfully pushed onto queue
    _totalItems++;
    return 1;
}


template <typename T>
T QueueArray<T>::Dequeue()
{
    /*Search for first nonempty queue, stop when reached end of _array*/
    int i = 0;
    while((_array[i].empty()) && (i < _size))
    {
        i++;
    }
    
    /* If we reached end of array and that last queue is not empty dequeue from 
     * it. */
    if(!(_array[i].empty()))
    {
        /* With both primitive data types and objects this line should work. In 
         * the event T  is an object, it should invoke the copy constructor. */
        T ret = _array[i].front(); 
        _array[i].pop();
        _totalItems--;
        return ret;
    }
    
    return 0;
}


template <typename T>
int QueueArray<T>::Asize() const
{
    return _size;
}

template <typename T>
int QueueArray<T>::QAsize() const
{
    return _totalItems;
}

template <typename T>
int QueueArray<T>::Qsize(int index) const
{
    if((index < 0) || (index > _size - 1))
        return -1;
    //Return value only if index is within bounds
    return (int)(_array[index].size());
}

template <typename T>
T* QueueArray<T>::Qstate(int index)
{
    if((index < 0) || (index > _size - 1))
        return NULL;
    size_t size = _array[index].size();
    queue<T> tempQueue(_array[index]);
    T* ret = new T[size];
    
    /* set the items of the array from the queue. This required popping the
     * items off. Just like before, if there was an object in here, it should 
     * invoke the copy constructor. */
    for(size_t i = 0; i < size; i++)
    {
        ret[i] = tempQueue.front();
        tempQueue.pop();
    }
    
    return ret;
}

#endif

