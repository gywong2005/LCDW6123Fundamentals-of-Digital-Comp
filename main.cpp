#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Validators

bool isValidName(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ' || c == '-') continue;
        return false;
    }
    return true;
}

bool ValidPhoneNmber(const string& s) {
    if (s.size() != 11) return false;
    for (char c : s) if (c < '0' || c > '9') return false;
    return true;
}

bool isValidAmount(double amount) { return amount >= 0.0; }\

///////////////////////////////////
//taru//

// -------------------- Account (string account number) --------------------
class Account {
private:
    string accNumber;   
    string name;
    double balance;
public:
    Account() : accNumber(""), name(""), balance(0.0) {}
    Account(const string& acc, const string& n, double b = 0.0)
        : accNumber(acc), name(n), balance(b) {}

    // getters
    string getAccNumber() const { return accNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    // setters
    void setName(const string& n) { name = n; }
    void setBalance(double b) { balance = b; }
    void deposit(double amount) {
        if (amount > 0) balance += amount;
        else cout << "Invalid deposit amount.\n";
    }
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) balance -= amount;
        else cout << "Invalid or insufficient funds.\n";
    }

    void display() const {
        cout << "Account Number: " << accNumber
             << " | Name: " << name
             << " | Balance: RM " << fixed << setprecision(2) << balance << '\n';
    }
};

class Node {
public:
    Account acc;
    Node* next;
    Node(const Account& a) : acc(a), next(nullptr) {}
};

// -------------------- AccountList (uses string keys) --------------------
class AccountList {
private:
    Node* head;
public:
    AccountList() : head(nullptr) {}
    ~AccountList() {
        Node* current = head;
        while (current) { Node* temp = current; current = current->next; delete temp; }
    }

    bool exists(const string& accNum) {
        Node* temp = head;
        while (temp) {
            if (temp->acc.getAccNumber() == accNum) return true;
            temp = temp->next;
        }
        return false;
    }

    void addAccount(const string& accNum, const string& name, double balance = 0.0) {
        if (exists(accNum)) { cout << "Account already exists!\n"; return; }
        Node* newNode = new Node(Account(accNum, name, balance));
        newNode->next = head; 
        head = newNode;
        cout << "Account added successfully.\n";
    }

    void displayAccounts() {
        if (!head) { cout << "No accounts found.\n"; return; }
        Node* temp = head; 
        while (temp) { temp->acc.display(); temp = temp->next; }
    }

    Node* search(const string& accNum) {
        Node* temp = head;
        while (temp) {
            if (temp->acc.getAccNumber() == accNum) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void deposit(const string& accNum, double amount) {
        Node* accNode = search(accNum);
        if (accNode) { accNode->acc.deposit(amount); cout << "Deposit successful.\n"; }
        else cout << "Account not found.\n";
    }

    void withdraw(const string& accNum, double amount) {
        Node* accNode = search(accNum);
        if (accNode) { accNode->acc.withdraw(amount); cout << "Withdrawal processed.\n"; }
        else cout << "Account not found.\n";
    }

    void deleteAccount(const string& accNum) {
        if (!head) { cout << "No accounts to delete.\n"; return; }

        if (head->acc.getAccNumber() == accNum) {
            Node* temp = head; head = head->next; delete temp;
            cout << "Account deleted successfully.\n"; 
            return;
        }

        Node* prev = head; 
        Node* curr = head->next;
        while (curr) {
            if (curr->acc.getAccNumber() == accNum) {
                prev->next = curr->next; 
                delete curr;
                cout << "Account deleted successfully.\n"; 
                return;
            }
            prev = curr; 
            curr = curr->next;
        }
        cout << "Account not found.\n";
    }

    bool saveToFile(const string& filename) const {
        ofstream out(filename, ios::trunc);
        if (!out) { 
            cout << "Error: cannot open file for writing: " << filename << "\n"; 
            return false; 
        }
        Node* temp = head;
        while (temp) {
            out << temp->acc.getAccNumber() << '\t'
                << temp->acc.getName() << '\t'
                << temp->acc.getBalance() << '\n';
            temp = temp->next;
        }
        return true;
    }

    bool loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) { return false; }

        // clear list
        Node* current = head;
        while (current) { Node* tmp = current; current = current->next; delete tmp; }
        head = nullptr;

        string line; 
        int loaded = 0;
        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string accStr, nameStr, balStr;
            if (!getline(ss, accStr, '\t')) continue;
            if (!getline(ss, nameStr, '\t')) continue;
            if (!getline(ss, balStr, '\t')) continue;

            try {
                double bal = stod(balStr);
                Node* newNode = new Node(Account(accStr, nameStr, bal));
                newNode->next = head; 
                head = newNode; 
                loaded++;
            } catch (...) {
                continue;
            }
        }
        if (loaded > 0) { cout << "Loaded " << loaded << " account(s) from file.\n"; }
        return true;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////
//shuyi//

// -------------------- main menu --------------------
int main() {
    AccountList bank;
    bank.loadFromFile("accounts.txt");

    int choice;
    string accNumStr, name, choiceStr;
    double amount;

    do {
        cout << "\n===== Grab Wallet =====\n";
        cout << "1. Add New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit (Top Up)\n";
        cout << "5. Withdraw (Manual)\n";
        cout << "6. Delete Account\n";
        cout << "7. Book GrabCar Ride\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        getline(cin, choiceStr);

        // validate menu choice
        try { choice = stoi(choiceStr); } catch (...) { cout << "Invalid choice.\n"; continue; }
        if (choice < 1 || choice > 8) { cout << "Invalid choice.\n"; continue; }

        switch (choice) {
        case 1: { // add
            cout << "Enter Phone number (11 digits 0-9): ";
            getline(cin, accNumStr);
            if (!ValidPhoneNmber(accNumStr)) { cout << "Invalid phone number!\n"; break; }

            cout << "Enter Customer Name: ";
            getline(cin, name);
            if (!isValidName(name)) { cout << "Invalid name! Use letters, spaces, or hyphens.\n"; break; }

            string amountStr;
            cout << "Enter Initial Balance: ";
            getline(cin, amountStr);
            try { amount = stod(amountStr); } catch (...) { cout << "Invalid balance! Must be a number.\n"; break; }
            if (!isValidAmount(amount)) { cout << "Invalid balance! Must be non-negative.\n"; break; }

            bank.addAccount(accNumStr, name, amount);
            bank.saveToFile("accounts.txt");
            break;
        }
        case 2: // list
            bank.displayAccounts();
            break;

        case 3: { // search
            cout << "Enter Phone Number to search: ";
            getline(cin, accNumStr);
            if (!ValidPhoneNmber(accNumStr)) { cout << "Invalid phone number!\n"; break; }
            if (Node* found = bank.search(accNumStr)) found->acc.display();
            else cout << "Account not found.\n";
            break;
        }

        case 4: { // deposit
            cout << "Enter Phone Number: ";
            getline(cin, accNumStr);
            if (!ValidPhoneNmber(accNumStr)) { cout << "Invalid phone number!\n"; break; }

            string amountStr;
            cout << "Enter Deposit Amount: ";
            getline(cin, amountStr);
            try { amount = stod(amountStr); } catch (...) { cout << "Invalid amount!\n"; break; }
            if (amount <= 0) { cout << "Invalid deposit amount!\n"; break; }

            bank.deposit(accNumStr, amount);
            bank.saveToFile("accounts.txt");
            break;
        }

        case 5: { // withdraw
            cout << "Enter Phone Number: ";
            getline(cin, accNumStr);
            if (!ValidPhoneNmber(accNumStr)) { cout << "Invalid phone number!\n"; break; }

            string amountStr;
            cout << "Enter Withdrawal Amount: ";
            getline(cin, amountStr);
            try { amount = stod(amountStr); } catch (...) { cout << "Invalid amount!\n"; break; }
            if (amount <= 0) { cout << "Invalid withdrawal amount!\n"; break; }

            bank.withdraw(accNumStr, amount);
            bank.saveToFile("accounts.txt");
            break;
        }

        case 6: { // delete
            cout << "Enter Phone Number to delete: ";
            getline(cin, accNumStr);
            if (!ValidPhoneNmber(accNumStr)) { cout << "Invalid phone number!\n"; break; }
            bank.deleteAccount(accNumStr);
            bank.saveToFile("accounts.txt");
            break;
        }

        case 7: { // GrabCar booking
            cout << "Enter Phone Number : ";
            getline(cin, accNumStr);
            if (!ValidPhoneNmber(accNumStr)) { cout << "Invalid phone number!\n"; break; }

            Node* user = bank.search(accNumStr);
            if (!user) { cout << "Phone Number not found.\n"; break; }

            cout << "\n--- GrabCar ---\n";
            cout << "Vehicle Types:\n";
            cout << "  1. Economy (base RM 3.00, RM 1.40/km)\n";
            cout << "  2. Premium (base RM 5.00, RM 2.50/km)\n";
            cout << "  3. 6-Seater (base RM 6.00, RM 2.00/km)\n";

            int vehicle;
            if (!readIntInRange("Choose vehicle (1-3): ", vehicle, 1, 3)) { cout << "Invalid vehicle choice.\n"; break; }

            int timeType;
            if (!readIntInRange("Select Time (1=Normal, 2=Peak): ", timeType, 1, 2)) { cout << "Invalid time choice.\n"; break; }
            bool isPeak = (timeType == 2);

            double distance;
            if (!readPositiveDouble("Enter trip distance (km): ", distance)) { cout << "Invalid distance.\n"; break; }

            double fare = calcGrabCarFare(vehicle, distance, isPeak);

            cout << fixed << setprecision(2);
            cout << "\n===== GrabCar Fare Summary =====\n";
            cout << "User: " << user->acc.getName() << " (+" << accNumStr << ")\n";
            cout << "Vehicle: " << (vehicle==1? "Economy" : vehicle==2? "Premium" : "6-Seater") << "\n";
            cout << "Time: " << (isPeak? "Peak" : "Normal") << "\n";
            cout << "Distance: " << distance << " km\n";
            cout << "Fare (to deduct): RM " << fare << "\n";
            cout << "Wallet Balance (before): RM " << user->acc.getBalance() << "\n";

            if (user->acc.getBalance() < fare) {
                cout << "Insufficient funds. Please top up.\n";
                break;
            }

            user->acc.withdraw(fare);
            bank.saveToFile("accounts.txt");
            cout << "Payment successful. Wallet Balance (after): RM " << user->acc.getBalance() << "\n";
            cout << "=================================\n";
            break;
        }

        case 8:
            cout << "Saving and exiting system...\n";
            bank.saveToFile("accounts.txt");
            break;
        }
    } while (choice != 8);

    return 0;
}