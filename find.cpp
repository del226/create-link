// Denny Li and using ChatGPT to figure it out
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
struct UserData {
  string lastname;
  string firstname;
  string email;
  string LIN;
  string username;
};

// Function to search for a username based on a full email
string getUsername(const string &fullEmail, const string &csvFilePath) {
  ifstream file(csvFilePath);
  string line;

  while (getline(file, line)) { // ChatGPT for this part
    istringstream iss(line);
    vector<string> tokens;
    string token;

    while (getline(iss, token, ',')) {
      tokens.push_back(token);
    }

    if (tokens.size() == 5) {
      UserData userData;
      userData.lastname = tokens[0];
      userData.firstname = tokens[1];
      userData.LIN = tokens[2];
      userData.email = tokens[3];
      userData.username = tokens[4];

      if (userData.email == fullEmail) {
        return userData.username;
      }
    }
  }

  return "Email not found"; // Email is not found
}

int main(int argc, char **argv) {
  string csvFilePath = "users.csv"; // File of all users
  string domain = "lehigh.edu";     // Domain name
  int clone = 0;
  if (argc > 1) { // Only when there are multiple args do it show git clone
    clone = 1;
    cout << "Will print git clone links" << endl;
  }
  // Ask for the project name (assumed to be the same for all users)
  string project;
  string className;
  cout << "Enter the class name: "; // Github class name (LU-ABC000)
  cin >> className;
  cout << "Enter the project name: "; // Github project name

  cin >> project;
  cout << "Using LU-" << className + "/" + project << endl;

  while (true) { // Forever until Ctrl-C or exit
    string input;
    cout << "Enter username ('abc123'): ";
    cin >> input;

    if (input == "exit") {
      break; // Exit the loop if the user enters 'exit'
    }

    // We can just do abc123 or abc123@lehigh.edu
    string user = input.substr(0, 6);

    string fullEmail = user + "@" + domain;
    string username = getUsername(fullEmail, csvFilePath);

    if (username != "Email not found") {

      string githubLink = "https://github.com/LU-" + className + "/" + project +
                          "-" + username; // Return GitHub link, Easy!
      cout << "GitHub link: " << githubLink << endl;
      if (clone) { // Print git clone link
        string gitClone = "git clone git@github.com:LU-" + className + "/" +
                          project + "-" + username + ".git";

        cout << "Git clone (SSH): " << gitClone << endl << endl;
      }
    } else {
      cout << "Email not found in the CSV file." << endl;
      string githubLinkFailed =
          "https://github.com/LU-" + className + "/" + project + "-" +
          input; // Return GitHub link for nonexistant user

      cout << "GitHub link (user input): " << githubLinkFailed << endl;
    }
  }

  return 0;
}
