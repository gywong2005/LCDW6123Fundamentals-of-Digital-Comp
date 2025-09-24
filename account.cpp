
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
----------------------give it another 10-20 then u push again----------------
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
----------------------give it another 10-20 then u push again----------------
class Node {
public:
    Account acc;
    Node* next;
    Node(const Account& a) : acc(a), next(nullptr) {}
};
