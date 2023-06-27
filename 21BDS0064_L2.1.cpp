#include <bits/stdc++.h>
using namespace std;

//Check operators
bool isSpecialChar(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
    {
        return true;
    }
    return false;
}

bool isValidIdentifier(char *str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isSpecialChar(str[0]))
    {
        return false;
    }
    if (strlen(str) == 1)
    {
        return true;
    }
    else
    {
        for (int i = 1; i < strlen(str); i++)
        {
            if (isSpecialChar(str[i]))
            {
                return false;
            }
        }
    }
    return true;
}

bool isValidConstant(char *str)
{
    int len = strlen(str);
    int numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        }
        else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' &&
                str[i] != '3' && str[i] != '4' && str[i] != '5' &&
                str[i] != '6' && str[i] != '7' && str[i] != '8' &&
                str[i] != '9' ||
            (str[i] == '-' && i > 0))
        {
            return false;
        }
    }

    return true;
}

char *getSubString(char *originalString, int left, int right)
{
    char *str = (char *)malloc(sizeof(char) * (right - left + 2));
    for (int i = left; i <= right; i++)
    {
        str[i - left] = originalString[i];
        str[right - left + 1] = '\0';
    }
    return str;
}
void  checkConstantsAndIdentifiers(string originalString)
{
    char str[1024];
    strcpy(str, originalString.c_str());
    int left = 0;
    int right = 0;
    int len = strlen(str);
    while (right <= len && left <= right)
    {
        if (!isSpecialChar(str[right]))
        {
            right++;
        }
        if (isSpecialChar(str[right]) && left == right)
        {
            right++;
            left = right;
        }
        if ((isSpecialChar(str[right]) && left != right) || (right == len && left != right))
        {
            char *sub = getSubString(str, left, right - 1);
            // Check for validity of Constant
            if (isValidConstant(sub))
            {
                cout << "'" << sub << "'"
                     << " is a VALID CONSTANT"
                     << endl;
            }
            else if (!isValidConstant(sub))
            {
                cout << "'" << sub << "'"
                     << " is NOT a VALID CONSTANT"
                     << endl;
            }
            // Check for validity of Identifier
            if (isValidIdentifier(sub) && !isSpecialChar(str[right - 1]))
            {
                cout << "'" << sub << "'"
                     << " is a VALID IDENTIFIER"
                     << endl;
            }
            else if (!isValidIdentifier(sub) && !isSpecialChar(str[right - 1]))
            {
                cout << "'" << sub << "'" << " is NOT a VALID IDENTIFIER"<< endl;
            }
            left = right;
            cout << endl;
        }
    }
}
int main()
{
    ifstream inputFile;
    string originalString = "";
    inputFile.open("file.txt");
    string inputLine;
    if (inputFile.is_open())
    {
        while (inputFile)
        {
            getline(inputFile, inputLine);
            originalString = originalString + inputLine;
        }
    }
    else
    {
        cout << "Couldn't open file" << endl;
    }
    checkConstantsAndIdentifiers(originalString);
    return 0;
}