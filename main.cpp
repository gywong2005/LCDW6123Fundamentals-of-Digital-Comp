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