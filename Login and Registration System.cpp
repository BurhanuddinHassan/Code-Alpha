#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


string hashPassword(const string& password) {
    stringstream ss;
    for (char ch : password) {
        ss << hex << setw(2) << setfill('0') << (int)(ch ^ 0x5A);
    }
    return ss.str();
}


void registerUser() {
    string username, password, hashedPassword;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    hashedPassword = hashPassword(password);


    ifstream file(username + ".txt");
    if (file.is_open()) {
        cout << "Username already exists. Please try another username." << endl;
        file.close();
        return;
    }


    ofstream userFile(username + ".txt");
    if (userFile.is_open()) {
        userFile << hashedPassword;
        userFile.close();
        cout << "Registration successful!" << endl;
    } else {
        cout << "Error: Could not create user file." << endl;
    }
}


void loginUser() {
    string username, password, hashedPassword, storedPassword;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    hashedPassword = hashPassword(password);


    ifstream userFile(username + ".txt");
    if (userFile.is_open()) {
        getline(userFile, storedPassword);
        userFile.close();

        if (storedPassword == hashedPassword) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Invalid username or password." << endl;
        }
    } else {
        cout << "User does not exist." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
