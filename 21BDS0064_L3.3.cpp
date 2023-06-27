#include <bits/stdc++.h>
using namespace std;

char *ip;
int i = 0;
char lastPro[6];
char Stack[50];
char prods[][4] = {")E(", "E*E", "E+E", "i"};
int TOS = 0;
int len;
char prec[9][9] = {
    /*       +    -    *    /    ^    i    (    )    $  */
    /* + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* ^ */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* i */ '>', '>', '>', '>', '>', 'e', 'e', '>', '>',
    /* ( */ '<', '<', '<', '<', '<', '<', '<', '>', 'e',
    /* ) */ '>', '>', '>', '>', '>', 'e', 'e', '>', '>',
    /* $ */ '<', '<', '<', '<', '<', '<', '<', '<', '>',
};

int indexOf(char);
void stackDisplay();
void displayInStr();
void shift();
int reduce();

int main()
{
    ip = new char[50];
    cout << "\nEnter the string: ";
    cin >> ip;

    ip = strcat(ip, "$");
    len = strlen(ip);
    strcpy(Stack, "$");

    cout << "\nSTACK \t\t ACTION" << endl;
    while (i <= len)
    {
        shift();

        cout << endl;
        stackDisplay();
        cout << "\t\t";
        cout << "Shift -> push ";

        if (prec[indexOf(Stack[TOS])][indexOf(ip[i])] == '>')
        {
            while (reduce())
            {
                cout << endl;
                stackDisplay();
                cout << "\t\t";
                cout << "E->" << lastPro;
            }
        }
    }

    if (strcmp(Stack, "$E$") == 0)
    {
        cout << "\n\nString is accepted";
    }
    else
    {
        cout << "\n\nString is not accepted";
    }

    delete[] ip;
    return 0;
}

int indexOf(char op)
{
    switch (op)
    {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '^':
        return 4;
    case 'i':
        return 5;
    case '(':
        return 6;
    case ')':
        return 7;
    case '$':
        return 8;
    default:
        return -1;
    }
}

void shift()
{
    Stack[++TOS] = *(ip + i++);
    Stack[TOS + 1] = '\0';
}

int reduce()
{
    int len, found;
    int t;
    for (int i = 0; i < 5; i++) // selecting productions
    {
        len = strlen(prods[i]);
        if (Stack[TOS] == prods[i][0] && TOS + 1 >= len)
        {
            found = 1;

            for (t = 0; t < len; t++)
            {
                if (Stack[TOS - t] != prods[i][t])
                {
                    found = 0;
                    break;
                }
            }

            if (found == 1)
            {
                Stack[TOS - t + 1] = 'E';
                TOS = TOS - t + 1;
                strcpy(lastPro, prods[i]);
                Stack[TOS + 1] = '\0';
                return 1; // Reduction completed
            }
        }
    }
    return 0;
}

void stackDisplay()
{
    for (int j = 0; j <= TOS; j++)
    {
        cout << Stack[j];
    }
}

void displayInStr()
{
    for (int j = i; j < len; j++)
    {
        cout << *(ip + j);
    }
}