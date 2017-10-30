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

void printUsers();
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
  
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 3; j++) {
      users[i][j] = "";
    }
  }

  // Create an administrator with admin priveledges
  createAdmin();

  // Create a login loop
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

// Print the Usernames
void printUsers() {
  cout << endl << "------ USERS -------" << endl;
  for(int i = 0; i < 5; i++) {
    cout << "User " << i << ": " << users[i][0] << endl;
  }
  cout << "--------------------" << endl;
}

// Creates and Administrator in users[0]
void createAdmin() {
  cout << ">> Create Administrator" << endl;
  if(!promptAdd()) {
    cout << "Administrator not created!" << endl;
  } else {
    cout << "Administrator created!" << endl; 
  }
  return;
}

// Deals with everything that an administrator is allowed to do while
// they are logged on. 
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
    printUsers();
  } else if(action == 2) {
    promptChangePass();
  } else if(action == 3) {
    promptDelete(); 
    printUsers();
  } else if(action == 4) {
    logout();
    return false;
  }else {
    cout << "Invalid Action number" << endl;
  }  
  return true;
}

// Deals with everything a regular user is allowed to do while they
// are logged on. 
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

// Prompts the admin to add a new user if there is room
int promptAdd() {
  bool nameTaken = true;
  if(numUsers >= 5) {
    cout << "Reached Max Users : Can't Create New User" << endl;
    return 0;
  }
  
  string name = "", pass = "";

  while(nameTaken) {
    cout << "New Username:" << endl;
    cin >> name;
    
    if(numUsers > 0) {
      for(int i = 0; i < numUsers; i++) {
        if(users[i][0] == name) {
          cout << "Username " << name << " is already taken!" << endl;
          nameTaken = true;
          break;
        } 
        nameTaken = false;
      }
    } else {
      nameTaken = false;
    }
    
  }

  cout << "New Password:" << endl;
  cin >> pass;
  
  return addUser(name, pass);
}

// Adds the user the the users array
int addUser(string name, string pass) {
  int nextUser = 0;
  for(int i = numUsers; i >= 0; i--) {
    if(users[i][0] == "") {
      nextUser = i;
    } 
  }
  
  string priv = "";
  if(numUsers == 0) {
    priv = "admin";
  } else {
    priv = "user";
  }
  users[nextUser][0] = name;
  users[nextUser][1] = pass;
  users[nextUser][2] = priv;
  
  numUsers++;
  return 1;
}

// Prompts a user to login
int promptLogin() {
  string name = "", pass = "";
  
  cout << "Username:" << endl;
  cin >> name;

  cout << "Password:" << endl;
  cin >> pass;
  
  return login(name, pass);
}

// Actually logs the user in
int login(string name, string pass) {
  for(int i = 0; i < numUsers; i++) {
    if(users[i][0] == name && users[i][1] == pass) {
      cout << "Logged in: " << name << endl;
      username = name;
      password = pass;
      return i;
    }
  }
  return -1;
}

// Logs out a user
void logout() {
  username = "";
  password = "";
  cout << "Logged Out!" << endl << endl;
}

// Prompts a user to change their password
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

// Actually changes the password in the users array
int changePass() {
  string newPass = "";
  cout << "Enter New Password: " << endl;
  cin >> newPass;

  for(int i = 0; i < numUsers; i++) {
    if(users[i][0] == username && users[i][1] == password) {
      users[i][1] = newPass;
      password = newPass;
      cout << "Password Changed!" << endl;
      return i;
    }
  }
  return -1;
}

// Prompts the admin to delete a user after they verify their password
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

// Actually deletes a user from the users array
int deleteUser() {
  string delUser = "";
  cout << "Enter the username of the user you want to delete: " << endl;
  cin >> delUser;

  for(int i = 0; i < numUsers; i++) {
    if(users[i][0] == delUser) {
       users[i][0] = "";
       users[i][1] = "";
       users[i][2] = "";
       cout << "Deleted " << delUser << "!" << endl;
       numUsers--;
       return 1;
    }
  }
  cout << "Username not found!" << endl;
  return 0;
}
