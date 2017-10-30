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

void createAdmin();
bool adminLoggedIn();
bool userLoggedIn();
int promptAdd();
int addUser(string name, string pass);
int promptLogin();
int login(string name, string pass);
void logout();
int promptChangePass();
int changePass();
int promptDelete();
int deleteUser();

string users[5][3];
int numUsers;
string username;
string password;

int main() 
{
  numUsers = 0;
  bool exit = false;
  int action = 0, priv = 0;
  username = "";
  password = "";

  createAdmin();

  while(!exit) {
    cout << endl;
    cout << "Select an action by typing it's corresponding number" << endl;
    cout << "1: Login" << endl;
    cout << "2: Exit" << endl;
    cout << "Action >> " ;

    cin >> action;
  
    if(action == 1) {
      priv = promptLogin();
      if(priv == 0) {
        while(adminLoggedIn()) { 
          cout << endl;
        }
      } else if(priv > 0) {
        while(userLoggedIn()) {
          cout << endl;
        }
      } else {
        cout << "Login Failed" << endl;
      }
    } else if(action == 2) {
      exit = true;
    } else {
      cout << "Invalid Action number" << endl;
    } 
  }

  return 0;
}

void createAdmin() {
  cout << ">> Create Administrator" << endl;
  if(!promptAdd()) {
    cout << "Administrator not created!" << endl;
  } else {
    cout << "Administrator created!" << endl; 
  }
  return;
}

bool adminLoggedIn() {
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
    promptAdd();
  } else if(action == 2) {
    promptChangePass();
  } else if(action == 3) {
    promptDelete(); 
  } else if(action == 4) {
    logout();
    return false;
  }else {
    cout << "Invalid Action number" << endl;
  }  
  return true;
}

bool userLoggedIn() {
  int action = 0;
  cout << endl;
  cout << "Select an action by typing it's corresponding number" << endl;
  cout << "1: Change Password" << endl;
  cout << "2: Logout" << endl;
  cout << "Action >> " ;

  cin >> action;
  if(action == 1) {
    promptChangePass();
  } else if(action == 2) {
    logout();
    return false;
  }else {
    cout << "Invalid Action number" << endl;
  }  
  return true;
}

int promptAdd() {
  string name = "", pass = "";

  cout << "New Username:" << endl;
  cin >> name;

  cout << "New Password:" << endl;
  cin >> pass;

  return addUser(name, pass);
}

int addUser(string name, string pass) {
  if(numUsers >= 5) {
    cout << "Reached Max Users" << endl;
    return 0;
  }
 
  string priv = "";
  if(numUsers == 0) {
    priv = "admin";
  } else {
    priv = "user";
  }
  users[numUsers][0] = name;
  users[numUsers][1] = pass;
  users[numUsers][2] = priv;
  numUsers++;
  return 1;
}

int promptLogin() {
  string name = "", pass = "";
  
  cout << "Username:" << endl;
  cin >> name;

  cout << "Password:" << endl;
  cin >> pass;
  
  return login(name, pass);
}

int login(string name, string pass) {
  for(int i = 0; i < 5; i++) {
    if(users[i][0] == name && users[i][1] == pass) {
      cout << "Logged in: " << name << endl;
      username = name;
      password = pass;
      return i;
    }
  }
  return -1;
}

void logout() {
  username = "";
  password = "";
  cout << "Logged Out!" << endl << endl;
}

int promptChangePass() {
  string verPass = "";
  cout << "Verify Password: " << endl;
  cin >> verPass;

  if(verPass == password) {
    changePass();
  } else {
    cout << "Incorrect Password" << endl;
  }

  return 1;
}

int changePass() {
  string newPass = "";
  cout << "Enter New Password: " << endl;
  cin >> newPass;

  for(int i = 0; i < 5; i++) {
    if(users[i][0] == username && users[i][1] == password) {
      users[i][1] = newPass;
      password = newPass;
      return i;
    }
  }
  return -1;
}

int promptDelete() {
  string verPass = "";
  cout << "Verify Password: " << endl;
  cin >> verPass;

  if(verPass == password) {
    deleteUser();
  } else {
    cout << "Incorrect Password" << endl;
  }

  return 1;
}

int deleteUser() {
  string delUser = "";
  cout << "Enter the username of the user you want to delete: " << endl;
  cin >> delUser;

  for(int i = 0; i < 5; i++) {
    if(users[i][0] == delUser) {
       users[i][0] = "";
       users[i][1] = "";
       users[i][2] = "";
       return 1;
    }
  }
  cout << "Username not found!" << endl;
  return 0;
}
