#include <iostream>
using namespace std;

/*
Updated Productions:
Q -> AbQ'
Q' -> ABQ' | e
A -> BA'
A' -> bA' | e
B -> a | b
e is null here
*/

bool Q();
bool Z();
bool A();
bool Y();
bool B();

char *currentPointer;
char *tempVar;

void outputStackString()
{
    if (*currentPointer != '\0')
    {
        cout << "Current Stack: ";
        for (char *c = currentPointer; *c != '\0'; c++)
        {
            cout << *c;
        }
        cout << endl;
        cout << "Current String: " << currentPointer << endl;
    }
}


bool Q()
{
    tempVar = currentPointer;
    if (A() && B())
    {
        outputStackString();
        if (*currentPointer == 'b')
        {
            currentPointer++;
            outputStackString();
            if (Z())
            {
                return true;
            }
        }
    }
    currentPointer = tempVar;
    outputStackString();
    return false;
}

bool Z()
{
    if (A())
    {
        if (B())
        {
            if (Z())
            {
                return true;
            }
        }
    }
    outputStackString();
    return true;
}

bool A()
{
    tempVar = currentPointer;
    if (B())
    {
        if (Y())
        {
            return true;
        }
    }
    currentPointer = tempVar;
    outputStackString();
    return false;
}

bool Y()
{
    tempVar = currentPointer;
    if (*currentPointer == 'b')
    {
        currentPointer++;
        outputStackString();
        if (Y())
        {
            return true;
        }
        currentPointer = tempVar;
        outputStackString();
        return false;
    }
    currentPointer = tempVar;
    outputStackString();
    return true;
}

bool B()
{
    tempVar = currentPointer;
    if (*currentPointer == 'a')
    {
        currentPointer++;
        outputStackString();
        return true;
    }
    else if (*currentPointer == 'b')
    {
        currentPointer++;
        outputStackString();
        return true;
    }
    currentPointer = tempVar;
    outputStackString();
    return false;
}

int main()
{
    cout << "Enter the string: ";
    string st;
    cin >> st;
    currentPointer = &st[0];
    outputStackString();
    if (Q() && *currentPointer == '\0')
    {
        cout << "The string: " << st << " is accepted." << endl;
    }
    else
    {
        cout << "The string: " << st << " is rejected." << endl;
    }
    return 0;
}
