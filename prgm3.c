/*Problem Statement:
Implement a stack data structure in C using a design-centric approach that emphasizes modularity, encapsulation, and error
handling.
Requirements:

• Define a stack structure (struct Stack) that holds an array of integers, the current size, and the maximum capacity.
• Write the following functions with proper error handling:
o Stack* createStack(int capacity) – Dynamically allocates and initializes a stack.
o void push(Stack* s, int item) – Adds an element to the stack; handles overflow.
o int pop(Stack* s) – Removes and returns the top element; handles underflow.
o bool isEmpty(Stack* s) – Checks if the stack is empty.*/
/*
 * Stack Implementation in C
 * -------------------------
 * Features:
 *   - Modular design: separate functions for each operation
 *   - Encapsulation: all stack details hidden inside struct
 *   - Error handling: safe checks for overflow/underflow
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   // for bool type

/* ----- STRUCTURE DEFINITION ----- */
typedef struct {
    int *arr;       // dynamically allocated array to hold stack elements
    int top;        // index of the top element (-1 when empty)
    int capacity;   // maximum number of elements
} Stack;

/* ----- FUNCTION DECLARATIONS ----- */
Stack* createStack(int capacity);
void push(Stack* s, int item);
int pop(Stack* s);
bool isEmpty(Stack* s);
void display(Stack* s);

/* Function: createStack
 * ----------------------
 * Dynamically allocates memory for a stack with given capacity.
 * Initializes top = -1 (empty).
 */
Stack* createStack(int capacity) {
    Stack* s = (Stack*) malloc(sizeof(Stack));
    if (!s) {
        printf("Error: Memory allocation failed.\n");
        exit(1);  // terminate safely if malloc fails
    }

    s->capacity = capacity;
    s->top = -1;   // stack starts empty
    s->arr = (int*) malloc(capacity * sizeof(int));

    if (!s->arr) {
        printf("Error: Memory allocation for stack array failed.\n");
        free(s);   // free already allocated memory
        exit(1);
    }

    return s;
}

/* Function: push
 * ----------------
 * Adds an element on top of the stack.
 * If the stack is full, prints error (overflow).
 */
void push(Stack* s, int item) {
    if (s->top == s->capacity - 1) {
        printf("Error: Stack Overflow. Cannot push %d.\n", item);
        return;
    }
    s->arr[++s->top] = item;   // increment top, then assign value
    printf("Pushed %d onto stack.\n", item);
}

/* Function: pop
 * --------------
 * Removes and returns the top element of the stack.
 * If the stack is empty, prints error (underflow).
 */
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Error: Stack Underflow. Cannot pop.\n");
        return -1;   // sentinel value to indicate failure
    }
    return s->arr[s->top--];   // return current top, then decrement
}

/* Function: isEmpty
 * ------------------
 * Returns true if stack has no elements.
 */
bool isEmpty(Stack* s) {
    return s->top == -1;
}

/* Function: display
 * ------------------
 * Prints all elements of the stack from top to bottom.
 */
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%d\n", s->arr[i]);
    }
}

/* ----- MAIN PROGRAM ----- */
int main() {
    int capacity, choice, value;
    Stack* s = NULL;

    printf("Enter stack capacity: ");
    scanf("%d", &capacity);

    s = createStack(capacity);   // create stack dynamically

    do {
        printf("\n====== Stack Menu ======\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Check if Empty\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(s, value);
                break;

            case 2:
                value = pop(s);
                if (value != -1)   // check valid pop
                    printf("Popped: %d\n", value);
                break;

            case 3:
                display(s);
                break;

            case 4:
                if (isEmpty(s))
                    printf("Stack is empty.\n");
                else
                    printf("Stack is not empty.\n");
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    free(s->arr);  // free dynamically allocated memory
    free(s);

    return 0;
}

