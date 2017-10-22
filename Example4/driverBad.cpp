//driverBad.cpp
//Wyatt Emery
//Shaya Wolf
//COSC 4010 Fall 2017
// last code update: 10-12-17 by Cybersecsy

#include<map>
#include<string>
#include<vector>
#include<iostream>
using namespace std;

struct DisjointSet
{
  //this maintains the data in the Disjoint set data structure
  //the first T is the value and the second T is the value it points to
  map<int, int> _parent;
  //this will keep track of the height of each tree.
  map<int, int> _treeHeight;
  
};
  void createDisjointSet(vector<int> data);
  /*Create a disjoint set with the vector of data specified. all elements 
   * will be placed into a set containing only themselves. duplicates 
   *  elements are removed in this process*/
  
  void setInsert(int value); //O(1)
  /*insert value and make it part of its own set*/
  
  void setInsert(int value, int set); //O(log(n))
  /*insert value into the specified set*/
  
  void setMerge(int set1, int set2); //O(log(n))
  /*Merge set1 and set2. Merging a value that is not in the disjoint set will 
   * add it to the set with its parent being the default constructor for that type 
   * and merge it with the other value. */
  
  int setFind(int value); //O(log(n))
  /*return the set that value is a part of*/
  void setPrint();//O(n)
  /*built-in way to see the contents of the disjoint set*/
    //helper function
int setFindRoot(int value); //O(log(n))


struct DisjointSet set;



int main()
{
  
  cout << "DisjointSet struct driver\n inserting numbers 1-10." << endl;
  
  for(int i = 1; i < 11; i++)
  {
    setInsert(i);
  }
  cout << "Set state: " << endl;
  setPrint();
  
  cout << "\n merging, 3 and 4, 8 and 2, 2 and 6" << endl;
  setMerge(3,4);
  setMerge(8,1);
  setMerge(2,6);
  cout << "Set state: " << endl;
  setPrint();
  
  cout << "\n merging 4 and 8, 9 and 3, 7 and 5" << endl;
  setMerge(4,8);
  setMerge(9,3);
  setMerge(7,5);
  cout << "Set state: " << endl;
  setPrint();
  
  cout << "\n Notice this created a second level in the tree since we merged to" 
  << "trees of the same depth. This is seen in that 3 is part of set 4 which is" 
  << "part of set 1." << endl;
  
  cout << "3 is in set:" << setFind(3) << "\n4 is in set:" << setFind(4) 
  << endl;
  
  cout << "\nWhat about invalid input?" << endl;
  
  cout << "merge on 50 and 25" << endl;
  setMerge(50,25);
  cout << "Set state: " << endl;
  setPrint();
  
  cout << "merge on 50 and 10" << endl;
  setMerge(50,10);
  cout << "Set state: " << endl;
  setPrint();
  
  cout << "\nmerge on 50 and 65" << endl;
  setMerge(50,65);
  cout << "Set state: " << endl;
  setPrint();
  
  cout << "\nfind on 100: ";
  cout << setFind(100) << endl;
  cout << "This looks as though it is part of set 0. However, it just returned"; 
  cout << " a null iterator object, which when printed by cout prints as a 0.\n";
  cout << "\nSet state: " << endl;
  setPrint();
  return 0;
}

void createDisjointSet(vector<int> data)
{
  for (auto t : data)
  {
    (set._parent)[t] = t;
    set._treeHeight[t] = 1;
  }
}

void setInsert(int value)
{
   (set._parent)[value] = value;
}

/*
 *    value will be placed in the set specified. the height
 *    of the tree will not grow unless the set currently being
 *    added to has height = 1
 *    //O(log(n))
 */
void setInsert(int value, int set)
{
  setInsert(value);
  setMerge(value, set);
}

/*
 *    set1 will be merged with set2. the height of the tree  of the 
 *    larger set will not grow unless both sets have the same tree height
 *    //O(log(n))
 */
void setMerge(int set1, int set2)
{
  int set1Root = setFindRoot(set1);
  int set2Root = setFindRoot(set2);
  if (set._treeHeight[set1Root] > set._treeHeight[set2Root])
  {
    set._parent[set2Root] = set1Root;
  }
  else if(set._treeHeight[set1Root] < set._treeHeight[set2Root])
  {
    set._parent[set1Root] = set2Root;
  }
  else
  {
    set._parent[set1Root] = set2Root;
    set._treeHeight[set2Root] += set._treeHeight[set1Root];
  }
}

/*
 *    returns the root of the set that value belongs to via a T object
 *    Makes use of the find function in the stl map class which is O(log(n))
 *    //O(log(n))
 */
int setFind(int value)
{
  return set._parent.find(value)->second;
}

void setPrint()
{
  cout << "item\tset" << endl;
  auto it = set._parent.begin();
  while (it != set._parent.end())
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
int setFindRoot(int value)
{
  int* rootptr = &value;
  while (*rootptr != set._parent[*rootptr])
  {
    rootptr = &set._parent[*rootptr];
  }
  return *rootptr;
}

