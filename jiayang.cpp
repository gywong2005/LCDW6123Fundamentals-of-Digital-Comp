
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