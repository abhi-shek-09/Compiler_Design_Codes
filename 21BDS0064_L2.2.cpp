#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isValidOperator(const string& op) {
    string validOps[] = { "+", "-", "*", "/", "%", "=", "==", "!=","--", "++", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>" };
    int numberOfOperators = sizeof(validOps) / sizeof(validOps[0]);
    for (int i = 0; i < numberOfOperators; i++) {
        if (op == validOps[i]) {
            return true;
        }
    }
    return false;
}

void analyzeOperators(const string& inputString) {
    string currentOperator = "";
    string resultString = "";
    for (size_t i = 0; i < inputString.length(); i++) {
        char ch = inputString[i];
        if (isspace(ch)) {
            if (!currentOperator.empty()) {
                if (isValidOperator(currentOperator)) {
                    resultString += currentOperator + " is a valid operator\n";
                }
                else {
                    resultString += currentOperator + " is not a valid operator\n";
                }
                currentOperator.clear();
            }
        }
        else {
            currentOperator += ch;
        }
    }

    if (!currentOperator.empty()) {
        if (isValidOperator(currentOperator)) {
            resultString += currentOperator + " is a valid operator\n";
        }
        else {
            resultString += currentOperator + " is not a valid operator\n";
        }
    }

    cout << resultString;
}

int main() {
    ifstream inputFile("test.txt");
    if (!inputFile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string lineString;
    while (getline(inputFile, lineString)) {
        analyzeOperators(lineString);
    }

    inputFile.close();
    return 0;
}
