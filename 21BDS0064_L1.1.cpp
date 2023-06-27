#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
using namespace std;

//Lexical Analysis
bool checkPunctuator(char c)                 
{
    if (c == ' ' || c == '+' || c == '-' || c == '*' ||
        c == '/' || c == ',' || c == ';' || c == '>' ||
        c == '<' || c == '=' || c == '(' || c == ')' ||
        c == '[' || c == ']' || c == '{' || c == '}' ||
        c == '&' || c == '|')
        {
            return true;
        }
    return false;
}

bool isIdentifier(char* st)                     
{
    if (st[0] == '0' || st[0] == '1' || st[0] == '2' ||
        st[0] == '3' || st[0] == '4' || st[0] == '5' ||
        st[0] == '6' || st[0] == '7' || st[0] == '8' ||
        st[0] == '9' || checkPunctuator(st[0]) == true)
        {
            return false;
        }                                   
    int i,length = strlen(st);
    if (length == 1)
    {
        return true;
    }                                       
    else
    {
    for (i = 1 ; i < length ; i++)                    
    {
        if (checkPunctuator(st[i]) == true)
        {
            return false;
        }
    }
    }
    return true;
}

bool checkOp(char c)                            //check if the given character is an operator or not
{
    if (c == '+' || c == '-' || c == '*' ||
        c == '/' || c == '>' || c == '<' ||
        c == '=' || c == '|' || c == '&')
    {
       return true;
    }
    return false;
}

bool checkKeyword(char *st)                       //check if the given substring is a keyword or not
{
    if (!strcmp(st, "if") || !strcmp(st, "else") ||
        !strcmp(st, "while") || !strcmp(st, "do") ||
        !strcmp(st, "break") ||  !strcmp(st, "continue")
        || !strcmp(st, "int") || !strcmp(st, "double")
        || !strcmp(st, "float") || !strcmp(st, "return")
        || !strcmp(st, "char") || !strcmp(st, "case")
        || !strcmp(st, "long") || !strcmp(st, "short")
        || !strcmp(st, "typedef") || !strcmp(st, "switch")
        || !strcmp(st, "unsigned") || !strcmp(st, "void")
        || !strcmp(st, "static") || !strcmp(st, "struct")
        || !strcmp(st, "sizeof") || !strcmp(st,"long")
        || !strcmp(st, "volatile") || !strcmp(st, "typedef")
        || !strcmp(st, "enum") || !strcmp(st, "const")
        || !strcmp(st, "union") || !strcmp(st, "extern")
        || !strcmp(st,"bool") || !strcmp(st,"print") || !strcmp(st,"endif") || !strcmp(st,"then"))
        {
            return true;
        }
    else
    {
       return false;
    }
}

bool checkNum(char* st)                            //check if the given substring is a number or not
{
    int index, length = strlen(st),numberOfDecimal = 0;
    if (length == 0)
    {
        return false;
    }
    for (index = 0 ; index < length ; index++)
    {
        if (numberOfDecimal > 1 && st[index] == '.')
        {
            return false;
        } else if (numberOfDecimal <= 1)
        {
            numberOfDecimal++;
        }
        if (st[index] != '0' && st[index] != '1' && st[index] != '2'
            && st[index] != '3' && st[index] != '4' && st[index] != '5'
            && st[index] != '6' && st[index] != '7' && st[index] != '8'
            && st[index] != '9' || (st[index] == '-' && index > 0))
            {
                return false;
            }
    }
    return true;
}

char* subString(char* realString, int left, int right)                
{
    int index;

    char* str = (char*) malloc(sizeof(char) * (right - left + 2));

    for (index = left; index <= right; index++)
    {
        str[index - left] = realString[index];
        str[right - left + 1] = '\0';
    }
    return str;
}

void printOpsWithoutDuplicates(vector<char> vtr){
    for (vector<char>::iterator itei = vtr.begin(); itei<vtr.end(); itei++) {
            char ch = *itei;
            for (vector<char>::iterator itej = itei+1; itej<vtr.end(); itej++) {
                if (ch == *itej) {
                    vtr.erase(itej);
                }
            }
        }

        for (int i=0; i<vtr.size(); i++) {
            cout<<vtr[i] << ' ';
        }
        cout<<endl;
}

void printWithoutDuplicates(vector<string> vtr){
    for (vector<string>::iterator itei = vtr.begin(); itei<vtr.end(); itei++) {
            string s = *itei;
            for (vector<string>::iterator itej = itei+1; itej<vtr.end(); itej++) {
                if (s == *itej) {
                    vtr.erase(itej);
                }
            }
        }

        for (int i=0; i<vtr.size(); i++) {
            cout<<vtr[i] << ' ';
        }
        cout<<endl;
}

void parse(string st)                       
{
    char str[1024];
    strcpy(str, st.c_str());
    int left = 0, right = 0;
    int len = strlen(str);

    vector<char> operators;
    vector<string> keywords;
    vector<string> numbers;
    vector<string> identifiers;

    while (right <= len && left <= right) {
        if (checkPunctuator(str[right]) == false)         
            {
                right++;
            }

        if (checkPunctuator(str[right]) == true && left == right)      
            {
            if (checkOp(str[right]) == true)
            {
               operators.push_back(str[right]);
            }
            right++;
            left = right;

            } else if (checkPunctuator(str[right]) == true && left != right
                   || (right == len && left != right))          
            {
            char* sub = subString(str, left, right - 1);   

            if (checkKeyword(sub) == true)
                        {
                           keywords.push_back(sub);
                        }
            else if (checkNum(sub) == true)
                        {
                            numbers.push_back(sub);
                        }
            else if (isIdentifier(sub) == true
                     && checkPunctuator(str[right - 1]) == false)
                     {
                            identifiers.push_back(sub);
                     }
            else if (isIdentifier(sub) == false
                     && checkPunctuator(str[right - 1]) == false)
                     {
                         cout<< sub <<" is not a valid identifier\n";
                     }

            left = right;
            }
    }

    cout << "Operators: ";
    printOpsWithoutDuplicates(operators);
    cout << "Keywords: ";
    printWithoutDuplicates(keywords);
    cout << "Numbers: ";
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout<<endl;
    cout << "Identifiers: ";
    printWithoutDuplicates(identifiers);


    return;

}

string removeAndPrintComments(string st){
    char str[1024];
    int commentStart = 0;
    int commentEnd = 0;
    strcpy(str, st.c_str());
    for(int i =0; i<st.length(); i++){
        if(str[i] == '/' && str[i+1] == '*'){
            commentStart = i;
            for(int j=i+1; j<st.length(); j++){
                if(str[j] == '*' && str[j+1] == '/'){
                    commentEnd = j;
                    break;
                }
            }
        }
    }

    if(commentStart && commentEnd){
        cout<<"Comments: ";
        for(int i=commentStart+3; i<commentEnd; i++){
            cout<<str[i];
        }
        st = st.replace(commentStart, commentEnd - commentStart, "");
    }
    cout<<endl;
    return st;
}


int main(){
    ifstream myfile;
    string total_String = "";
    myfile.open("input.txt");
    string myline;
    if ( myfile.is_open() ) {
        while ( myfile ) { 
            getline (myfile, myline);
            total_String += myline;
        }
    }
    else {
        cout << "Couldn't open file\n";
    }
    string new_String = removeAndPrintComments(total_String);
    parse(total_String);
    return 0;
}