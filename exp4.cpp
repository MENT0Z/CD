#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <set>

using namespace std;

// Function to remove left recursion from a grammar
void removeLeftRecursion(map<string, vector<string>>& grammar) {
    map<string, vector<string>> newGrammar;

    for (auto& nonTerminal : grammar) {
        string A = nonTerminal.first;
        vector<string> productions = nonTerminal.second;

        vector<string> beta, alpha;
        for (string prod : productions) {
            if (prod[0] == A[0]) {
                // Left recursive production (starts with A)
                alpha.push_back(prod.substr(1)); // Remove the leading 'A' from the production
            } else {
                // Non-left recursive production
                beta.push_back(prod);
            }
        }

        // If we have left recursion
        if (!alpha.empty()) {
            string A_prime = A + "'";

            // Add new production rules for A'
            for (string b : beta) {
                newGrammar[A].push_back(b + A_prime);  // A -> beta A'
            }
            for (string a : alpha) {
                newGrammar[A_prime].push_back(a + A_prime);  // A' -> alpha A'
            }
            newGrammar[A_prime].push_back("ε"); // A' -> epsilon (ε)
        } else {
            // No left recursion, retain the original productions
            newGrammar[A] = beta;
        }
    }

    // Print the new grammar after left recursion removal
    for (auto& nonTerminal : newGrammar) {
        cout << nonTerminal.first << " -> ";
        for (string prod : nonTerminal.second) {
            cout << prod << " | ";
        }
        cout << endl;
    }
}

// Function to perform left factoring
void leftFactoring(map<string, vector<string>>& grammar) {
    map<string, vector<string>> newGrammar;

    for (auto& nonTerminal : grammar) {
        string A = nonTerminal.first;
        vector<string> productions = nonTerminal.second;

        // Step 1: Group productions by common prefixes
        map<string, vector<string>> prefixMap;
        for (string prod : productions) {
            string prefix = prod.substr(0, 1);  // Get the first character of the production
            prefixMap[prefix].push_back(prod.substr(1)); // Store the rest of the production after the prefix
        }

        // Step 2: If there's more than one common prefix, perform left factoring
        if (prefixMap.size() > 1) {
            string A_prime = A + "'";  // New non-terminal for factoring

            for (auto& prefix : prefixMap) {
                string prefixProd = prefix.first;
                newGrammar[A].push_back(prefixProd + A_prime); // A -> prefix A'
                for (string subProd : prefix.second) {
                    newGrammar[A_prime].push_back(subProd); // A' -> remaining parts of each production
                }
            }
        } else {
            // No left factoring needed
            newGrammar[A] = productions;
        }
    }

    // Print the new grammar after left factoring
    for (auto& nonTerminal : newGrammar) {
        cout << nonTerminal.first << " -> ";
        for (string prod : nonTerminal.second) {
            cout << prod << " | ";
        }
        cout << endl;
    }
}

int main() {
    map<string, vector<string>> grammar;
    string input, line, nonTerminal, production;

    // Ask user for grammar input
    cout << "Enter the grammar:" << endl;
    cout << "For each non-terminal, enter its productions separated by '|'. Example: S -> aSb | abS" << endl;

    // Read the grammar from the user input
    while (true) {
        cout << "Enter a non-terminal (or type 'end' to finish): ";
        getline(cin, nonTerminal);

        if (nonTerminal == "end") {
            break;
        }

        cout << "Enter productions for " << nonTerminal << " (separate with '|' ): ";
        getline(cin, input);

        // Parse the input into productions
        stringstream ss(input);
        while (getline(ss, production, '|')) {
            grammar[nonTerminal].push_back(production);
        }
    }
    // Print the original grammar
    cout << "\nOriginal Grammar:" << endl;
    for (const auto& rule : grammar) {
        cout << rule.first << " -> ";
        for (const string& prod : rule.second) {
            cout << prod << " | ";
        }
        cout << endl;
    }
    // Perform Left Recursion Removal
    cout << "\nGrammar after Left Recursion Removal:" << endl;
    removeLeftRecursion(grammar);

    cout << endl;

    // Perform Left Factoring
    cout << "\nGrammar after Left Factoring:" << endl;
    leftFactoring(grammar);

    return 0;
}
