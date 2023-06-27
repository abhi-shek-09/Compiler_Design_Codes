#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

// Production rules for the grammar
const vector<string> productions = {
    "",     // Placeholder for the 0th production
    "E->E*T",
    "E->T",
    "T->T+F",
    "T->F",
    "F->(E)",
    "F->id"
};

// Parsing table for CLR parser
unordered_map<char, unordered_map<string, int>> parsingTable = {
    {'E', {{"id", 2}, {"(", 1}}},
    {'T', {{"id", 4}, {"(", 4}}},
    {'F', {{"id", 6}, {"(", 5}}}
};

// Stack to store parser states
stack<int> StackforState;

// Function to perform the parsing process
void parse(const string& input) {
    StackforState.push(0);
    int inpInd = 0;

    while (!StackforState.empty()) {
        int currSt = StackforState.top();
        char currSym = input[inpInd];

        if (isalpha(currSym) || currSym == '(' || currSym == ')') {
            string currToken;
            int nextInd = inpInd;
            while (isalpha(input[nextInd])) {
                currToken += input[nextInd];
                nextInd++;
            }
            if (currToken.empty()) {
                currToken = string(1, currSym);
                nextInd++;
            }
            inpInd = nextInd;

            int act = parsingTable[currSt][currToken];

            if (act > 0) {
                StackforState.push(act);
            } else if (act < 0) {
                int prodInd = -act;
                string prod = productions[prodInd];

                cout << "Reduce: " << prod << endl;

                for (int i = 0; i < prod.length() - 3; i++) {
                    StackforState.pop();
                }

                currSt = StackforState.top();
                char nonTer = prod[0];
                int nextSt = parsingTable[currSt][string(1, nonTer)];

                StackforState.push(nextSt);
            } else {
                cout << "Error! Unable to parse input." << endl;
                return;
            }
        } else if (currSym == '$' && currSt == 1) {
            cout << "Input successfully parsed." << endl;
            return;
        } else {
            cout << "Error! Unable to parse input." << endl;
            return;
        }
    }

    cout << "Error! Unable to parse input." << endl;
}

int main() {
    string input;
    cin>>input;
    parse(input);

    return 0;
}