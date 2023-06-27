#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;
struct Token {
  char tokentype;
  int tokenval;
};

Token currentToken;
string input;
int currInd = 0;
Token getnextToken() {
  Token token;
  if (currInd<input.length()) {
    if (isdigit(input[currInd])) {
      token.tokentype='D';
      token.tokenval=input[currInd]-'0';
      currInd++;
    } 
    else {
      token.tokentype = input[currInd];
      token.tokenval = 0;
      currInd++;
    }
  } 
  else {
    token.tokentype = '$';
    token.tokenval = 0;
  }
  return token;
}

void match(char expType) {
  if (currentToken.tokentype == expType) {
    currentToken = getnextToken();
  } 
  else {
    cout << "Syntax Error: Expected '" << expType << "', found '" <<currentToken.tokentype << "'\n";
    exit(0);
  }
}

int factor() {
  int result = 0;
  if (currentToken.tokentype == 'D') {
    result = currentToken.tokenval;
    match('D');
    cout << "Intermediate Result: " << result << endl;
  } else {
    cout << "Syntax Error: Expected digit, found '" <<
      currentToken.tokentype << "'\n";
    exit(0);
  }
  return result;
}

int term(){
  int res = factor();
  while (currentToken.tokentype == '*') {
    match('*');
    int factorval = factor();
    res *= factorval;
    cout << "Intermediate Result: " << res << endl;
  }
  return res;
}

int expr() {
  int res = term();
  while (currentToken.tokentype == '+') {
    match('+');
    int termval = term();
    res += termval;
    cout << "Intermediate Result: " << res << endl;
  }
  return res;
}

void evaluateExpression() {
  currentToken = getnextToken();
  int res = expr();
  cout<<"Final Result: "<<res<<endl;
}

int main() {
  cout << "Enter an expression: ";
  cin >> input;
  evaluateExpression();
  return 0;
}