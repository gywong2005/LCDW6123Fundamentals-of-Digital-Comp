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