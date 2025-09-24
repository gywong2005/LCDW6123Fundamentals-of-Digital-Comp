// -------------------- input helpers --------------------
bool readIntInRange(const string& prompt, int& out, int lo, int hi) {
    string s;
    cout << prompt;
    if (!getline(cin, s)) return false;
    if (s.empty()) return false;
    try {
        int v = stoi(s);
        if (v < lo || v > hi) return false;
        out = v; 
        return true;
    } catch (...) { 
        return false; 
    }
}
----------------------give it another 10-20 then u push again----------------
bool readPositiveDouble(const string& prompt, double& out) {
    string s; 
    cout << prompt;
    if (!getline(cin, s)) return false;
    if (s.empty()) return false;
    try {
        double v = stod(s);
        if (v <= 0) return false;
        out = v; 
        return true;
    } catch (...) { 
        return false; 
    }
}