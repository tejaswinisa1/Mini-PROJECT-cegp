/*Problem Statement:
Implement a simple calculator in C using the Command Pattern to separate user input from execution logic, promoting flexibility
and maintainability.

Requirements:
• Define a command interface (using function pointers in C) that supports:
o int (*execute)(int a, int b) – Performs an operation (add, subtract, multiply, divide).
o void (*undo)(int* result) – Reverts the last operation (optional).
• Implement concrete commands for:
o Addition, Subtraction, Multiplication, Division (handle division by zero).
• Create an invoker (a struct or function) that:
o Takes user input (two numbers and an operation).
o Executes the appropriate command.
o Stores a history of operations (for undo functionality, if implemented).*/
/*
 * Simple Calculator using Command Pattern in C
 * --------------------------------------------
 * Features:
 *   - Uses function pointers to implement Command Pattern
 *   - Supports Addition, Subtraction, Multiplication, Division
 *   - Handles division by zero safely
 *   - Maintains history of last operation for Undo
 */

#include <stdio.h>
#include <stdlib.h>

/* ----- COMMAND INTERFACE ----- */
typedef struct Command {
    int (*execute)(int a, int b);      // performs the operation
    void (*undo)(int* result, int b);  // reverts last operation
} Command;

/* ----- CONCRETE COMMANDS ----- */

// ADDITION
int add(int a, int b) { return a + b; }
void undoAdd(int* result, int b) { *result -= b; } // reverse by subtracting

// SUBTRACTION
int subtract(int a, int b) { return a - b; }
void undoSubtract(int* result, int b) { *result += b; } // reverse by adding

// MULTIPLICATION
int multiply(int a, int b) { return a * b; }
void undoMultiply(int* result, int b) {
    if (b != 0) *result /= b;  // reverse by dividing (if possible)
}

// DIVISION
int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return a;  // return unchanged
    }
    return a / b;
}
void undoDivide(int* result, int b) { *result *= b; } // reverse by multiplying

/* ----- INVOKER ----- */
typedef struct {
    int currentResult;   // holds latest result
    Command* lastCommand; // pointer to last used command
    int lastOperand;     // store last b (for undo)
} Calculator;

/* Executes chosen command */
void executeCommand(Calculator* calc, Command* cmd, int a, int b) {
    calc->currentResult = cmd->execute(a, b);  // run operation
    calc->lastCommand = cmd;                   // remember command
    calc->lastOperand = b;                     // remember operand
    printf("Result: %d\n", calc->currentResult);
}

/* Undo last command if available */
void undoCommand(Calculator* calc) {
    if (calc->lastCommand == NULL) {
        printf("No operation to undo.\n");
        return;
    }
    calc->lastCommand->undo(&(calc->currentResult), calc->lastOperand);
    printf("Undo performed. Result: %d\n", calc->currentResult);
}

/* ----- MAIN PROGRAM ----- */
int main() {
    // Define commands
    Command addCmd = {add, undoAdd};
    Command subCmd = {subtract, undoSubtract};
    Command mulCmd = {multiply, undoMultiply};
    Command divCmd = {divide, undoDivide};

    // Calculator state
    Calculator calc = {0, NULL, 0};

    int choice, a, b;

    do {
        printf("\n===== Simple Calculator =====\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Undo Last Operation\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                executeCommand(&calc, &addCmd, a, b);
                break;

            case 2:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                executeCommand(&calc, &subCmd, a, b);
                break;

            case 3:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                executeCommand(&calc, &mulCmd, a, b);
                break;

            case 4:
                printf("Enter two numbers: ");
                scanf("%d %d", &a, &b);
                executeCommand(&calc, &divCmd, a, b);
                break;

            case 5:
                undoCommand(&calc);
                break;

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
