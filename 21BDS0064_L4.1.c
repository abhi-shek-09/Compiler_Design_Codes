#include <stdio.h>
#include <string.h>

char stack[30];
int top = -1;

void push(char c) {
    top++;
    stack[top] = c;
}

char pop() {
    char ch;
    if (top != -1) {
        ch = stack[top];
        top--;
        return ch;
    }
    return 'x';
}

void printStack() {
    int j;
    printf("\n\t\t\t $");
    for (j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

int main() {
    FILE *text_file = fopen("inputFile.txt", "r");
    if (text_file == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    char inputStr[50];
    if (fgets(inputStr, sizeof(inputStr), text_file) == NULL) {
        printf("Failed to read the expression from the file.\n");
        fclose(text_file);
        return 1;
    }

    fclose(text_file);
    printf("\n Input Expression is: %s", inputStr);
    int l = strlen(inputStr);
    printf("\n\t\t $");
    for (int i = 0; i < l; i++) {
        if (inputStr[i] == 'i' && inputStr[i + 1] == 'd') {
            inputStr[i] = ' ';
            inputStr[i + 1] = 'E';
            printStack();
            printf("id");
            push('E');
            printStack();
        } else if (inputStr[i] == '+' || inputStr[i] == '-' || inputStr[i] == '*' || inputStr[i] == '/') {
            push(inputStr[i]);
            printStack();
        }
    }
    printStack();
    while (top >= 0) {
        char char1 = pop();
        if (char1 == 'x') {
            printf("\n\t\t\t $");
            break;
        }
        if (char1 == '+' || char1 == '-' || char1 == '*' || char1 == '/') {
            char char2 = pop();
            if (char2 != 'E') {
                printf("Error");
                return 1;
            } else {
                push('E');
                printStack();
            }
        }
    }
    return 0;
}