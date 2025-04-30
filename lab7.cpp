#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cctype>
using namespace std;

map<char, vector<string>> productions;
map<char, set<char>> leading, trailing;
set<char> visitedLeading, visitedTrailing;

bool isTerminal(char c) {
    return !isupper(c);  // Uppercase letters are Non-terminals
}

void computeLeading(char symbol) {
    if (visitedLeading.count(symbol)) return;
    visitedLeading.insert(symbol);

    for (string prod : productions[symbol]) {
        if (prod.empty()) continue;

        char first = prod[0];
        if (isTerminal(first)) {
            leading[symbol].insert(first);
        } else {
            if (prod.length() > 1 && isTerminal(prod[1])) {
                leading[symbol].insert(prod[1]);
            }
            computeLeading(first);
            for (char x : leading[first]) {
                leading[symbol].insert(x);
            }
        }
    }
}

void computeTrailing(char symbol) {
    if (visitedTrailing.count(symbol)) return;
    visitedTrailing.insert(symbol);

    for (string prod : productions[symbol]) {
        if (prod.empty()) continue;

        char last = prod[prod.length() - 1];
        if (isTerminal(last)) {
            trailing[symbol].insert(last);
        } else {
            if (prod.length() > 1 && isTerminal(prod[prod.length() - 2])) {
                trailing[symbol].insert(prod[prod.length() - 2]);
            }
            computeTrailing(last);
            for (char x : trailing[last]) {
                trailing[symbol].insert(x);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Enter productions (e.g. E->E+T):" << endl;

    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;
        if (input.length() < 4 || input[1] != '-' || input[2] != '>') {
            cout << "Invalid production format: " << input << endl;
            continue;
        }
        char lhs = input[0];
        string rhs = input.substr(3);
        productions[lhs].push_back(rhs);
    }

    for (auto& p : productions) {
        computeLeading(p.first);
        computeTrailing(p.first);
    }

    cout << "\nLEADING sets:\n";
    for (auto& p : leading) {
        cout << "LEADING(" << p.first << ") = { ";
        for (char c : p.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }

    cout << "\nTRAILING sets:\n";
    for (auto& p : trailing) {
        cout << "TRAILING(" << p.first << ") = { ";
        for (char c : p.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }

    return 0;
}