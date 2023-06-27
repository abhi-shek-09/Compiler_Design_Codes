#include <bits/stdc++.h>
using namespace std;

string findFirst(map<char, vector<string>> grammar, char nonTerminal){
    if (nonTerminal == '^' || !(nonTerminal >= 'A' && nonTerminal <= 'Z')){
        return string(1, nonTerminal);
    }

    string result = "";
    for (int i = 0; i < grammar[nonTerminal].size(); i++){
        string production = grammar[nonTerminal][i];
        bool checkNext = true;
        for (int j = 0; j < production.length() && checkNext; j++){
            checkNext = false;
            if (production[j] == '^' || !(production[j] >= 'A' && production[j] <= 'Z')){
                if (result.find(production[j]) == string::npos){
                    result.push_back(production[j]);
                }
            }
            else{
                string temp = findFirst(grammar, production[j]);
                for (int k = 0; k < temp.length(); k++){
                    if (temp[k] == '^'){
                        checkNext = true;
                    }
                    else if (result.find(temp[k]) == string::npos)
                    {
                        result.push_back(temp[k]);
                    }
                }
                if (checkNext && j == production.length() - 1)
                {
                    result.push_back('^');
                }
            }
        }
    }
    return result;
}

string findFirstOfString(map<char, vector<string>> grammar, string str)
{
    string result = "";
    bool checkNext = true;
    for (int j = 0; j < str.length() && checkNext; j++)
    {
        checkNext = false;
        if (str[j] == '^' || !(str[j] >= 'A' && str[j] <= 'Z'))
        {
            if (result.find(str[j]) == string::npos)
            {
                result.push_back(str[j]);
            }
        }
        else
        {
            string temp = findFirst(grammar, str[j]);
            for (int k = 0; k < temp.length(); k++)
            {
                if (temp[k] == '^')
                {
                    checkNext = true;
                }
                else if (result.find(temp[k]) == string::npos)
                {
                    result.push_back(temp[k]);
                }
            }
            if (checkNext && j == str.length() - 1)
            {
                result.push_back('^');
            }
        }
    }
    if (result == "")
    {
        return "^";
    }
    return result;
}

string findFollow(map<char, vector<string>> grammar, char startSymbol, char nonTerminal)
{
    string result = "";
    if (startSymbol == nonTerminal)
    {
        result.push_back('$');
    }
    for (map<char, vector<string>>::iterator it = grammar.begin(); it != grammar.end(); it++)
    {
        for (int j = 0; j < it->second.size(); j++)
        {
            if (it->second[j].find(nonTerminal) == string::npos)
            {
                continue;
            }
            string temp = "";
            bool parent = false;
            for (int a = 0; a < it->second[j].length(); a++)
            {
                parent = false;
                if (it->second[j][a] == nonTerminal)
                {
                    if (a == it->second[j].length() - 1)
                    {
                        parent = true;
                    }
                    else
                    {
                        temp = findFirstOfString(grammar, it->second[j].substr(a + 1, it->second[j].length() - a - 1));
                        for (int k = 0; k < temp.length(); k++)
                        {
                            if (temp[k] == '^')
                            {
                                parent = true;
                                continue;
                            }
                            if (result.find(temp[k]) == string::npos)
                            {
                                result.push_back(temp[k]);
                            }
                        }
                    }
                    if (parent)
                    {
                        if (nonTerminal == it->first)
                        {
                            continue;
                        }
                        temp = findFollow(grammar, startSymbol, it->first);
                        for (int k = 0; k < temp.length(); k++)
                        {
                            if (result.find(temp[k]) == string::npos)
                            {
                                result.push_back(temp[k]);
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main(){
    map<char, vector<string>> grammar;
    int numTerminals, numProductions;
    cout << "Enter the number of terminals: ";
    cin >> numTerminals;
    map<char, int> terminals;
    for (int i = 0; i < numTerminals; i++){
        char terminal;
        cin >> terminal;
        terminals[terminal] = i;
    }
    terminals['$'] = numTerminals;
    cout << "Enter the number of productions: ";
    cin >> numProductions;
    cout << "Enter the productions: " << endl;
    char startSymbol;

    for (int i = 0; i < numProductions; i++){
        char nonTerminal;
        string production;
        cin >> nonTerminal;
        if (i == 0){
            startSymbol = nonTerminal;
        }
        cout << " -> ";
        cin >> production;
        grammar[nonTerminal].push_back(production);
    }

    cout << "Given grammar is:" << endl << endl;
    for (map<char, vector<string>>::iterator it = grammar.begin(); it != grammar.end(); it++){
        cout << it->first << " -> ";
        for (int j = 0; j < it->second.size(); j++){
            cout << it->second[j];
            if (j != it->second.size() - 1){
                cout << " | ";
            }
        }
        cout << endl;
    }

    vector<vector<string>> parseTable(grammar.size(), vector<string>(numTerminals + 1, ""));

    for (map<char, vector<string>>::iterator it = grammar.begin(); it != grammar.end(); it++){
        for (int j = 0; j < it->second.size(); j++){
            string production = it->second[j];
            string firstSet = findFirstOfString(grammar, production);
            bool hasNull = false;
            for (int k = 0; k < firstSet.length(); k++){
                if (firstSet[k] == '^'){
                    hasNull = true;
                    continue;
                }
                string generatedProduction = "";
                generatedProduction += it->first;
                generatedProduction += " -> ";
                generatedProduction += production;
                parseTable[it->first - 'A'][terminals[firstSet[k]]] = generatedProduction;
            }
            if (hasNull){
                string followSet = findFollow(grammar, startSymbol, it->first);
                for (int k = 0; k < followSet.length(); k++){
                    string generatedProduction = "";
                    generatedProduction += it->first;
                    generatedProduction += " -> ^";
                    parseTable[it->first - 'A'][terminals[followSet[k]]] = generatedProduction;
                }
            }
        }
    }

    cout << endl << endl;
    cout << "Non-terminals \\ Terminals | ";

    vector<char> terminalSymbols(numTerminals + 1);
    for (map<char, int>::iterator it = terminals.begin(); it != terminals.end(); it++){
        terminalSymbols[it->second] = it->first;
    }
    for (int i = 0; i < terminalSymbols.size(); i++){
        cout << "     " << terminalSymbols[i] << "     | ";
    }
    cout << endl;
    int row = 0;
    for (map<char, vector<string>>::iterator it = grammar.begin(); it != grammar.end(), row < parseTable.size(); it++, row++){
        cout << " \t\t\t " << it->first << " \t\t\t |";
        for (int j = 0; j < parseTable[row].size(); j++)
        {
            cout << " " << parseTable[row][j] << " |";
        }
        cout << endl;
    }
    return 0;
}
