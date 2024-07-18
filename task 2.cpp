#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class UserDatabase {
private:
    unordered_map<string, string> users; 

public:
    bool registerUser(const string& username, const string& password) {
        if (users.find(username) != users.end()) {
            cout << "Username already exists. Please choose a different username." << endl;
            return false;
        }

        users[username] = password;
        saveToFile(username, password);
        cout << "Registration successful for user '" << username << "'." << endl;
        return true;
    }

    void saveToFile(const string& username, const string& password) {
        ofstream outfile("UserFiles/" + username + ".txt");
        if (outfile.is_open()) {
            outfile << "Username: " << username << endl;
            outfile << "Password: " << password << endl;
            outfile.close();
        } else {
            cout << "Error: Unable to create user file." << endl;
        }
    }

    bool authenticateUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second == password) {
            cout << "Authentication successful. Welcome, " << username << "!" << endl;
            return true;
        }
        cout << "Invalid credentials. Please check your username and password." << endl;
        return false;
    }
};

int main() {
    cout << "Welcome to the User Registration and Authentication System!" << endl;

    UserDatabase database;
    int choice;

    do {
        cout << "\n1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                database.registerUser(username, password);
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                database.authenticateUser(username, password);
                break;
            }
            case 3:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    } while (choice != 3);

    return 0;
}
