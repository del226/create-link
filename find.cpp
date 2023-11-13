// Denny Li and using ChatGPT to figure it out
#include <iostream>
#include <fstream>
#include <sstream>
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
string getUsername(const string& fullEmail, const string& csvFilePath) {
    ifstream file(csvFilePath);
    string line;

    while (getline(file, line)) { // ChatGPT for this part
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss,token,',')) {
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

int main() {
    string csvFilePath = "users.csv"; // File of all users
    string domain = "lehigh.edu"; // Domain name

    // Ask for the project name (assumed to be the same for all users)
    string project;
    string className;
    cout << "Enter the class name: "; //Github class name (LU-ABC000)
    cin >> className;
    cout << "Enter the project name: "; //Github project name
    
    cin >> project;
    cout << "Using LU-" << className+"/"+project<<endl;

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
            
            string githubLink = "https://github.com/LU-"+className+"/" + project + "-" + username; // Return GitHub link, Easy!
            
            string gitClone = "git clone git@github.com:LU-"+className+"/"+project + "-"+ username+".git";
            cout << "GitHub link: " << githubLink << endl;
            cout << "Git clone (SSH): " << gitClone << endl << endl;

        } else {
            cout << "Email not found in the CSV file." << endl;
        }
    }

    return 0;
}

