// driver.cpp
// Wyatt Emery
// Shaya Wolf
// COSC 4010/5012
// Fall 2017

#include <iostream>

using std::cin;
using std::cout;
using std::string;
using std::endl;

string users[5][3];
int numUsers, action;
string username, name;
string password, pass;
bool exitProg, logout, loggedin, deleted, changed, added;

void printUsers() {
  cout << endl << "------ USERS -------" << endl;
  for(int i = 0; i < numUsers; i++) {
    cout << "User " << i << ": " << users[i][0] << " -- " << users[i][1] << endl;
  }
  cout << "--------------------" << endl;
}

int main() 
{
  numUsers = 0;
  exitProg = false, logout = false, deleted = false, changed = false, added = false;
  action = 0;
  username = "";
  password = "";
  name = "";
  pass = "";

  // Create an administrator with admin priveledges
  cout << ">> Create First User" << endl;

  cout << "New Username:" << endl;
  cin >> name;

  cout << "New Password:" << endl;
  cin >> pass;
  
  users[numUsers][0] = name;
  users[numUsers][1] = pass;
  numUsers++;
  

  // Create a login loop
  while(!exitProg) {
    printUsers();
    cout << endl;
    cout << "Select an action by typing it's corresponding number" << endl;
    cout << "1: Login" << endl;
    cout << "2: Exit" << endl;
    cout << "Action >> " ;

    cin >> action;
  
    if(action == 1) {
      // Log in User   
      cout << "Username:" << endl;
      cin >> name;

      cout << "Password:" << endl;
      cin >> pass;
      
      loggedin = false;
      logout = false;
      for(int i = 0; i < numUsers; i++) {
        if(users[i][0] == name && users[i][1] == pass) {
          cout << "Logged in: " << name << endl;
          username = name;
          password = pass;
          loggedin = true;
        }
      }
      
      if(loggedin) {
        // Deals with everything that an administrator is allowed to do while
        // they are logged on.... like havok and chaos
        while(!logout) {
          printUsers();
          int action = 0;
          cout << endl;
          cout << "Select an action by typing it's corresponding number" << endl;
          cout << "1: Create a New User" << endl;
          cout << "2: Change Password" << endl;
          cout << "3: Delete a User" << endl;
          cout << "4: Logout" << endl;
          cout << "Action >> " ;

          cin >> action;
          if(action == 1) {
            // Add A user 
            cout << "New Username:" << endl;
            cin >> name;

            cout << "New Password:" << endl;
            cin >> pass;
            
            users[numUsers][0] = name;
            users[numUsers][1] = pass;
            numUsers++;
          } else if(action == 2) {
            // Change Password
            string verPass = "";
            cout << "Verify Password: " << endl;
            cin >> verPass;

            if(verPass == password) {
              string newPass = "";
              cout << "Enter New Password: " << endl;
              cin >> newPass;

              for(int i = 0; i < numUsers; i++) {
                if(users[i][0] == username && users[i][1] == password) {
                  users[i][1] = newPass;
                  password = newPass;
                  cout << "Password Changed!" << endl;
                }
              }
            } else {
              cout << "Incorrect Password" << endl;
            }
          } else if(action == 3) {
            // Delete a user
            string verPass = "";
            cout << "Verify Password: " << endl;
            cin >> verPass;

            if(verPass == password) {
              string delUser = "";
              cout << "Enter the username of the user you want to delete: " << endl;
              cin >> delUser;

              for(int i = 0; i < numUsers; i++) {
                if(users[i][0] == delUser) {
                  users[i][0] = "";
                  users[i][1] = "";
                  users[i][2] = "";
                  cout << delUser << " deleted!";
                }
              }
            } else {
              cout << "Incorrect Password" << endl;
            } 
          } else if(action == 4) {
            // Logout
            username = "";
            password = "";
            cout << "Logged Out!" << endl << endl;
            logout = true;
          }else {
            cout << "Invalid Action number" << endl;
          } 
          cout << endl;
        }
      } else {
        cout << "Login Failed" << endl;
      }
    } else if(action == 2) {
      exitProg = true;
    } else {
      cout << "Invalid Action number" << endl;
    } 
  }

  return 0;
}