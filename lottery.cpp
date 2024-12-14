#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

// Structure to store user information
struct User {
    int userId;
    string name;
    string email;
    string password;

    // Constructor to initialize a user
    User(int id, string n, string e, string p) : userId(id), name(n), email(e), password(p) {}
};

// Function to register a user
User registerUser() {
    int id;
    string name, email, password;

    cout << "Enter your User ID: ";
    cin >> id;
    cin.ignore(); // Ignore the newline character after entering ID
    cout << "Enter your Name: ";
    getline(cin, name);
    cout << "Enter your Email: ";
    getline(cin, email);
    cout << "Enter your Password: ";
    getline(cin, password);

    // Create and return a User object
    return User(id, name, email, password);
}

// Function to generate unique random numbers
void generateRandomNumbers(vector<long long>& numbers, int count, mt19937& generator, unordered_set<long long>& usedNumbers) {
    uniform_int_distribution<long long> distribution(10000, 99999);
    while (numbers.size() < count) {
        long long number = distribution(generator);
        if (usedNumbers.find(number) == usedNumbers.end()) { // Ensure uniqueness
            numbers.push_back(number);
            usedNumbers.insert(number); // Track used numbers to avoid duplicates
        }
    }
}

// Function to check if any of the tickets won
int checkTickets(const vector<long long>& userTickets, const unordered_set<long long>& winningNumbers) {
    int winningCount = 0;

    // Iterate through the user's tickets and check if they match any of the winning numbers
    for (long long ticket : userTickets) {
        if (winningNumbers.find(ticket) != winningNumbers.end()) { // If the ticket is a winning number
            winningCount++;
        }
    }
    return winningCount;
}

// Function to display winning numbers and their availability
void displayWinningNumbers(const vector<long long>& winningNumbers, const vector<long long>& prizeAmounts, const vector<bool>& isTaken) {
    cout << setw(10) << "Rank" << setw(15) << "Lotto Number" << setw(20) << "Prize Amount" << setw(15) << "Sold?" << endl;
    cout << "-------------------------------------------------------------\n";
    for (size_t i = 0; i < winningNumbers.size(); ++i) {
        cout << setw(10) << (i + 1)
             << setw(15) << winningNumbers[i]
             << setw(20) << prizeAmounts[i]
             << setw(15) << (isTaken[i] ? "Yes" : "No") << endl;
    }
}

int main() {
    const int numWinningTickets = 10; // Total number of winning tickets
    vector<long long> winningNumbers; // Vector to store the winning numbers
    vector<long long> prizeAmounts = {3000000, 1200000, 800000, 400000, 250000, 150000, 100000, 50000, 30000, 25000}; // Corresponding prize amounts
    vector<bool> isTaken(numWinningTickets, false); // To track if a prize has been taken
    unordered_set<long long> usedNumbers; // Set to track all the used ticket numbers
    random_device rd;
    mt19937 generator(rd()); // Random number generator

    // Generate the winning tickets
    generateRandomNumbers(winningNumbers, numWinningTickets, generator, usedNumbers);

    while (true) {
        string startResponse;
        cout << "Welcome to the Loto system! Would you like to start the program? (yes/no): ";
        cin >> startResponse;

        if (startResponse == "no" || startResponse == "No") {
            cout << "Thank you for using the Loto system. Goodbye!" << endl;
            break;
        }

        // User registration before proceeding
        cout << "\nRegister as a user to continue.\n";
        User currentUser = registerUser();
        cout << "User Registration Successful! Welcome, " << currentUser.name << "!\n";

        // Display options to the user
        int choice;
        cout << "\nPlease choose one of the following options:\n";
        cout << "1. Buy lottery tickets\n";
        cout << "2. Check a specific lottery ticket\n";
        cout << "3. View winning lottery numbers\n";
        cout << "Enter 1, 2, or 3: ";
        cin >> choice;

        if (choice == 1) {
            // User wants to buy lottery tickets
            int numTickets;
            cout << "\nHow many tickets would you like to buy? ";
            cin >> numTickets;

            // Generate the user's tickets using random numbers
            vector<long long> userTickets;
            generateRandomNumbers(userTickets, numTickets, generator, usedNumbers);

            // Ask if the user wants to see their lottery numbers before displaying them
            char seeTicketsChoice;
            cout << "\nWould you like to see your lottery numbers? (y/n): ";
            cin >> seeTicketsChoice;

            if (seeTicketsChoice == 'y' || seeTicketsChoice == 'Y') {
                cout << "\nYour tickets:\n";
                for (long long ticket : userTickets) {
                    cout << ticket << endl;
                }
            }

            // Ask if the user wants to check their tickets for any winners
            char checkChoice;
            cout << "\nWould you like to check if any of your tickets won? (y/n): ";
            cin >> checkChoice;

            if (checkChoice == 'y' || checkChoice == 'Y') {
                int winningCount = checkTickets(userTickets, unordered_set<long long>(winningNumbers.begin(), winningNumbers.end()));

                // Display the results of the check
                if (winningCount == 0) {
                    cout << "None of your tickets won. Better luck next time!\n";
                } else {
                    cout << winningCount << " of your tickets won! Congratulations!\n";
                }
            }

        } else if (choice == 2) {
            // User wants to check a specific lottery ticket
            long long userloto;
            cout << "Enter your 5-digit lottery number to check if it won: ";
            cin >> userloto;

            // Validate input: must be a 5-digit number
            if (userloto < 10000 || userloto > 99999) {
                cout << "Invalid number. Please enter a valid 5-digit number.\n";
                continue;
            }

            // Check if the user's lottery number matches any of the winning numbers
            if (find(winningNumbers.begin(), winningNumbers.end(), userloto) != winningNumbers.end()) {
                cout << "Congratulations! Your lottery number " << userloto << " won a prize!\n";
            } else {
                cout << "Sorry, your lottery number " << userloto << " did not win. Better luck next time!\n";
            }

        } else if (choice == 3) {
            // Display the winning numbers and their prizes
            cout << "\nHere are the current winning lottery numbers:\n";
            displayWinningNumbers(winningNumbers, prizeAmounts, isTaken);
        }
    }

    return 0;
}
