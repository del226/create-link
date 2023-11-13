// Denny Li and using ChatGPT to figure it out
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct UserData {
    std::string lastname;
    std::string firstname;
    std::string email;
    std::string LIN; 
    std::string username;
};

// Function to search for a username based on a full email (ChatGPT)
std::string getUsernameFromFullEmail(const std::string& fullEmail, const std::string& csvFilePath) {
    std::ifstream file(csvFilePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(iss,token,',')) {
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
    std::string csvFilePath = "users.csv"; // File of all users
    std::string domain = "lehigh.edu"; // Domain name

    // Ask for the project name (assumed to be the same for all users)
    std::string project;
    std::cout << "Enter the project name: "; //Github project name
    std::cin >> project;

    while (true) { // Forever until Ctrl-C or exit
        std::string input;
        std::cout << "Enter username ('abc123'): ";
        std::cin >> input;

        if (input == "exit") {
            break; // Exit the loop if the user enters 'exit'
        }

        // We can just do abc123 or abc123@lehigh.edu
        std::string user = input.substr(0, 6);

        std::string fullEmail = user + "@" + domain;
        std::string username = getUsernameFromFullEmail(fullEmail, csvFilePath);

        if (username != "Email not found") {
            
            std::string githubLink = "https://github.com/LU-CSE109/" + project + "-" + username; // Return GitHub link, Easy!
            
            std::string gitClone = "git clone git@github.com:LU-CSE109/"+project + "-"+ username+".git";
            std::cout << "GitHub link: " << githubLink << std::endl;
            std::cout << "Git clone (SSH): " << gitClone << std::endl << std::endl;

        } else {
            std::cout << "Email not found in the CSV file." << std::endl;
        }
    }

    return 0;
}

