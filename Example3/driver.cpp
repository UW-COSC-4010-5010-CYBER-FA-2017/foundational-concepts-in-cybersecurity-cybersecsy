//driver.cpp
//Wyatt Emery
//Shaya Wolf
//COSC 4010 Fall 2017
// last code update: 10-12-17 by Cybersecsy


#include"DisjointSet.hpp"
#include<iostream>
using namespace std;


int main()
{
  DisjointSet<int> set;
  
  cout << "DisjointSet driver\n inserting numbers 1-10." << endl;
  
  for(int i = 1; i < 11; i++)
  {
    set.insert(i);
  }
  cout << "Set state: " << endl;
  set.print();
  
  cout << "\n merging, 3 and 4, 8 and 2, 2 and 6" << endl;
  set.merge(3,4);
  set.merge(8,1);
  set.merge(2,6);
  cout << "Set state: " << endl;
  set.print();
  
  cout << "\n merging 4 and 8, 9 and 3, 7 and 5" << endl;
  set.merge(4,8);
  set.merge(9,3);
  set.merge(7,5);
  cout << "Set state: " << endl;
  set.print();
  
  cout << "\n Notice this created a second level in the tree since we merged to" 
  << "trees of the same depth. This is seen in that 3 is part of set 4 which is" 
  << "part of set 1." << endl;
  
  cout << "3 is in set:" << set.find(3) << "\n4 is in set:" << set.find(4) 
  << endl;
  
  cout << "\nWhat about invalid input?" << endl;
  
  cout << "merge on 50 and 25" << endl;
  set.merge(50,25);
  cout << "Set state: " << endl;
  set.print();
  
  cout << "merge on 50 and 10" << endl;
  set.merge(50,10);
  cout << "Set state: " << endl;
  set.print();
  
  cout << "\nmerge on 50 and 65" << endl;
  set.merge(50,65);
  cout << "Set state: " << endl;
  set.print();
  
  cout << "\nfind on 100: ";
  cout << set.find(100) << endl;
  cout << "This looks as though it is part of set 0. However, it just returned"; 
  cout << " a null iterator object, which when printed by cout prints as a 0.\n";
  cout << "\nSet state: " << endl;
  set.print();
  return 0;
}

