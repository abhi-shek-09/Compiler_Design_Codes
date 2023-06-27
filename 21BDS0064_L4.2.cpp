#include <bits/stdc++.h>
using namespace std;

struct SLRItem
{
    string production;
    int dot;
    char lookahead;
};


vector<SLRItem> getAugmentedGrammar(vector<string> grammar)
{
    vector<SLRItem> augGram;
    for (int i = 0; i < grammar.size(); i++)
    {
        string prod = grammar[i];
        SLRItem item = {prod, 0, prod[0]};
        augGram.push_back(item);
    }

    return augGram;
}


vector<SLRItem> findClosure(vector<SLRItem> itemSet)
{
    vector<SLRItem> closure;

    for (SLRItem item : itemSet)
    {
        closure.push_back(item);
        int item_len = item.production.length();
        for (int i = 1; i < item_len; i++)
        {
            if (item.production[i] == '.')
            {
                SLRItem newItem = {item.production, i, item.lookahead};

                if (find_if(closure.cbegin(), closure.cend(), [&newItem](const SLRItem &item) { return item.production == newItem.production && item.dot == newItem.dot && item.lookahead == newItem.lookahead; }) == closure.cend())
                {
                    closure.push_back(newItem);
                }
            }
        }
    }

    return closure;
}


vector<char> getFollow(string nonTerminal, vector<SLRItem> grammar)
{
    vector<char> follow;
    for (SLRItem item : grammar){
        int item_len = item.production.length();
        for (int i = 1; i < item_len; i++){
            if (item.production[i] == nonTerminal[0]){
                if (i == item_len - 1){
                    follow.push_back('$');
                }
                else{
                    follow.push_back(item.production[i + 1]);
                }
            }
        }
    }
    return follow;
}


vector<pair<string, int>> constructSLRParsingTable(vector<SLRItem> grammar)
{
    vector<pair<string, int>> parsingTable;
    int size = grammar.size();
    for (int i = 0; i < size; i++){
        SLRItem item = grammar[i];
        int item_len = item.production.length();
        
        for (; item.dot < item_len; item.dot++){
            char currentSymbol = item.production[item.dot];

            if (currentSymbol != '>' && currentSymbol != '-'){
                int nextState = item.dot == item_len - 1 ? -1 : i + 1;
                parsingTable.push_back(make_pair("shift", nextState));
            }
        }

        if (item.dot == item_len){
            vector<char> follow = getFollow(string(1, item.lookahead), grammar);
            for (char followSymbol : follow){
                parsingTable.push_back(make_pair("reduce", item_len));
            }
        }
    }

    return parsingTable;
}

void parseString(string str, vector<pair<string, int>> parsingTable){
    stack<int> stateStack;
    stack<char> symbolStack;

    stateStack.push(0);

    cout << "Parsing Steps:\n";
    for (char c : str){
        symbolStack.push(c);

        while (true){
            int state = stateStack.top();
            int nextState = parsingTable[state].second;
            string action = parsingTable[state].first;

            if (action == "shift"){
                cout << "Shift " << c << endl;
                stateStack.push(nextState);
                break;
            }
            else if (action == "reduce"){
                int reduceLen = parsingTable[state].second;
                string production = "";
                cout << "Reduce by " << production << endl;

                for (int i = 0; i < reduceLen; i++){
                    stateStack.pop();
                    symbolStack.pop();
                }

                char nonTerminal = production[0];
                int currentState = stateStack.top();
                int newState = parsingTable[currentState].second;
                symbolStack.push(nonTerminal);
                stateStack.push(newState);
                cout << "Shift " << nonTerminal << endl;
            }
            else{
                cout << "Parsing failed\n";
                return;
            }
        }

        cout << "Stack: ";
        stack<char> tempStack = symbolStack;

        while (!tempStack.empty()){
            cout << tempStack.top();
            tempStack.pop();
        }
        cout << endl;
    }
    cout << "\nParsing successful.\n";
}

void printTable(vector<pair<string, int>> parsingTable){
    cout << "\nSLR Parsing Table:\n";
    cout << "State      Action\n";
    for (int i = 0; i < parsingTable.size(); i++)
    {
        cout << "  " << i << "        "<< parsingTable[i].first<< endl;
    }
    cout << endl;
}

int main(){
    string input;
    cout << "\nEnter the input string: ";
    cin >> input;

    vector<string> grammar = {"Q->QAB|Ab", "A->Ab|B", "B->a|b"};
    vector<SLRItem> augmentedGrammar = getAugmentedGrammar(grammar);
    vector<pair<string, int>> parsingTable = constructSLRParsingTable(augmentedGrammar);

    cout << "\nThe productions used in SLR parsing are: " << endl;
    for (int i = 0; i < 3; i++){
        cout << grammar[i] << endl;
    }

    printTable(parsingTable);
    parseString(input, parsingTable);
    return 0;
}