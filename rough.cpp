#include<bits/stdc++.h>
using namespace std;

// Data structure to hold Grammar
struct Grammar {
    string nonTerminal;
    vector<string> productions;
};

// To store FIRST and FOLLOW sets
map<string, set<string>> FIRST, FOLLOW;
map<string, vector<string>> parsingTable;
vector<Grammar> grammar;

// Function to remove left recursion from a grammar
void removeLeftRecursion() {
    vector<Grammar> newGrammar;
   
    for (int i = 0; i < grammar.size(); i++) {
        Grammar A = grammar[i];
       
        vector<string> alpha, beta;
        for (string production : A.productions) {
            if (production[0] == A.nonTerminal[0]) { // Left recursion
                alpha.push_back(production.substr(1));
            } else {
                beta.push_back(production);
            }
        }

        if (!alpha.empty()) {
            string A_prime = A.nonTerminal + "'";
            // Create new productions
            Grammar A_primeGrammar;
            A_primeGrammar.nonTerminal = A_prime;
            for (string a : alpha) {
                A_primeGrammar.productions.push_back(a + A_prime);
            }
            A_primeGrammar.productions.push_back("ε"); // epsilon production

            newGrammar.push_back(A_primeGrammar);
            for (string b : beta) {
                newGrammar.push_back({A.nonTerminal, {b + A_prime}});
            }
        } else {
            newGrammar.push_back(A);
        }
    }
    grammar = newGrammar;
}

// Function to compute FIRST sets
void computeFIRST() {
    bool changes = true;
    while (changes) {
        changes = false;
        for (Grammar G : grammar) {
            string A = G.nonTerminal;
            for (string production : G.productions) {
                int i = 0;
                bool hasEpsilon = true;
                while (i < production.size() && hasEpsilon) {
                    string symbol = string(1, production[i]);
                    if (symbol == "ε") {
                        FIRST[A].insert("ε");
                        break;
                    }
                    if (isupper(symbol[0])) { // Non-terminal
                        if (!FIRST[symbol].empty()) {
                            FIRST[A].insert(FIRST[symbol].begin(), FIRST[symbol].end());
                        }
                        if (FIRST[symbol].find("ε") == FIRST[symbol].end()) {
                            hasEpsilon = false;
                        }
                    } else { // Terminal
                        FIRST[A].insert(symbol);
                        hasEpsilon = false;
                    }
                    i++;
                }
            }
        }
    }
}

// Function to compute FOLLOW sets
void computeFOLLOW() {
    FOLLOW[grammar[0].nonTerminal].insert("$");
    bool changes = true;
    while (changes) {
        changes = false;
        for (Grammar G : grammar) {
            string A = G.nonTerminal;
            for (string production : G.productions) {
                for (int i = 0; i < production.size(); i++) {
                    string B = string(1, production[i]);
                    if (isupper(B[0])) { // Non-terminal
                        int j = i + 1;
                        if (j < production.size()) {
                            string nextSymbol = string(1, production[j]);
                            if (isupper(nextSymbol[0])) {
                                FOLLOW[B].insert(FIRST[nextSymbol].begin(), FIRST[nextSymbol].end());
                            } else {
                                FOLLOW[B].insert(nextSymbol);
                            }
                        } else {
                            FOLLOW[B].insert(FOLLOW[A].begin(), FOLLOW[A].end());
                        }
                    }
                }
            }
        }
    }
}

// Function to construct parsing table
void constructParsingTable() {
    for (Grammar G : grammar) {
        string A = G.nonTerminal;
        for (string production : G.productions) {
            set<string> firstSet = FIRST[A];
            if (firstSet.find("ε") != firstSet.end()) {
                for (string b : FOLLOW[A]) {
                    parsingTable[A + "->" + production].push_back(b);
                }
            } else {
                for (string terminal : firstSet) {
                    parsingTable[A + "->" + production].push_back(terminal);
                }
            }
        }
    }
}

// Function to print the FIRST sets
void printFIRST() {
    for (auto &entry : FIRST) {
        cout << "FIRST(" << entry.first << ") = { ";
        for (auto &symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }
}

// Function to print the FOLLOW sets
void printFOLLOW() {
    for (auto &entry : FOLLOW) {
        cout << "FOLLOW(" << entry.first << ") = { ";
        for (auto &symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }
}

// Function to print the parsing table
void printParsingTable() {
    for (auto &entry : parsingTable) {
        cout << entry.first << " -> { ";
        for (auto &symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }
}

int main() {
    int numRules;
    cout << "Enter the number of grammar rules: ";
    cin >> numRules;
    cin.ignore();  // To consume the newline character left by cin
   
    for (int i = 0; i < numRules; i++) {
        string rule;
        cout << "Enter grammar rule " << i + 1 << ": ";
        getline(cin, rule);

        stringstream ss(rule);
        string nonTerminal;
        ss >> nonTerminal;

        vector<string> productions;
        string production;
        while (ss >> production) {
            productions.push_back(production);
        }

        grammar.push_back({nonTerminal, productions});
    }

    // Remove left recursion if necessary
    removeLeftRecursion();

    // Compute FIRST and FOLLOW sets
    computeFIRST();
    computeFOLLOW();

    // Construct the parsing table
    constructParsingTable();

    // Print the results
    cout << "\nFIRST sets:\n";
    printFIRST();

    cout << "\nFOLLOW sets:\n";
    printFOLLOW();

    cout << "\nParsing Table:\n";
    printParsingTable();

    return 0;
}