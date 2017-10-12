//DisjointSet.h
//Wyatt Emery
//Shaya Wolf
//COSC 4010 Fall 2017
// last code update: 3/21/16, by Wyatt Emery

/*
 *    Implements the Disjoint set Data structure. because the class is a templated class
 *    it will accept all types of input for use. the union and find are implemented such
 *    that both have complexity log(n).
 *    both the set and value types are the same because the sets are just an illusion.
 *    one T object "points" to another T object and the root or set name is the T object
 *    that points to itself.
 *    In most cases O(log(n)) refers to n being the height of the specific tree of values,
 *    which will be kept to a minimum.
 */


#include<map>
#include<string>
#include<vector>
#include<iostream>
using namespace std;

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

template<typename T>
class DisjointSet
{
private:
  //this maintains the data in the Disjoint set data structure
  //the first T is the value and the second T is the value it points to
  map<T, T> _parent;
  //this will keep track of the height of each tree.
  map<T, int> _treeHeight;
public:
  
  DisjointSet();
  /* Create an empty disjoint set*/
  
  DisjointSet(vector<T> data);
  /*Create a disjoint set with the vector of data specified. all elements 
   * will be placed into a set containing only themselves. duplicates 
   *  elements are removed in this process*/
  
  void insert(T value); //O(1)
  /*insert value and make it part of its own set*/
  
  void insert(T value, T set); //O(log(n))
  /*insert value into the specified set*/
  
  void merge(T set1, T set2); //O(log(n))
  /*Merge set1 and set2. Merging a value that is not in the disjoint set will 
   * add it to the set with its parent being the default constructor for that type 
   * and merge it with the other value. */
  
  T find(T value) const; //O(log(n))
  /*return the set that value is a part of*/
  void print() const;//O(n)
  /*built-in way to see the contents of the disjoint set*/
  private:
    //helper function
    T findRoot(T value); //O(log(n))
};


template<typename T>
DisjointSet<T>::DisjointSet()
{}

template<typename T>
DisjointSet<T>::DisjointSet(vector<T> data)
{
  for (auto t : data)
  {
    _parent[t] = t;
    _treeHeight[t] = 1;
  }
}

template<typename T>
void DisjointSet<T>::insert(T value)
{
  _parent[value] = value;
}

/*
 *    value will be placed in the set specified. the height
 *    of the tree will not grow unless the set currently being
 *    added to has height = 1
 *    //O(log(n))
 */
template<typename T>
void DisjointSet<T>::insert(T value, T set)
{
  _parent[value] = value;
  merge(value, set);
}

/*
 *    set1 will be merged with set2. the height of the tree  of the 
 *    larger set will not grow unless both sets have the same tree height
 *    //O(log(n))
 */
template<typename T>
void DisjointSet<T>::merge(T set1, T set2)
{
  T set1Root = findRoot(set1);
  T set2Root = findRoot(set2);
  if (_treeHeight[set1Root] > _treeHeight[set2Root])
  {
    _parent[set2Root] = set1Root;
  }
  else if(_treeHeight[set1Root] < _treeHeight[set2Root])
  {
    _parent[set1Root] = set2Root;
  }
  else
  {
    _parent[set1Root] = set2Root;
    _treeHeight[set2Root] += _treeHeight[set1Root];
  }
}

/*
 *    returns the root of the set that value belongs to via a T object
 *    Makes use of the find function in the stl map class which is O(log(n))
 *    //O(log(n))
 */
template<typename T>
T DisjointSet<T>::find(T value) const
{
  return _parent.find(value)->second;
}

template<typename T>
void DisjointSet<T>::print() const
{
  cout << "item\tset" << endl;
  auto it = _parent.begin();
  while (it != _parent.end())
  {
    cout << it->first << ":\t" << it->second << endl;
    it++;
  }
}

/*
 *    Helper function.
 *    simply locates and returns the root of the tree that any given value
 *    belongs to. 
 *    //O(log(n))
 */
template<typename T>
T DisjointSet<T>::findRoot(T value)
{
  T* rootptr = &value;
  while (*rootptr != _parent[*rootptr])
  {
    rootptr = &_parent[*rootptr];
  }
  return *rootptr;
}


#endif


