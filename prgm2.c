/*Problem Statement:
Write a C program that reads a series of integers from a user, stores them in an array, and calculates the mean and standard
deviation.
Requirements:
• Use defensive programming principles:
o Check input bounds (maximum 100 numbers).
o Handle invalid, non-integer, or out-of-range inputs gracefully.
• Organize your code into clear, single-purpose functions (e.g., input, validation, computation).
• Include detailed in-code comments describing how errors are detected and handled.
• Summarize (in 100-150 words) how your code design ensures robustness and prevents common runtime errors.*/#include <stdio.h>
#include <stdlib.h>   // for exit()
#include <math.h>     // for sqrt()
#include <string.h>   // for strtok

#define MAX_NUMBERS 100   // prevent buffer overflow

/* ----- FUNCTION DECLARATIONS ----- */
int getInput(int numbers[]);
double calculateMean(int numbers[], int count);
double calculateStdDev(int numbers[], int count, double mean);

/* Function: getInput
 * -------------------
 * Reads 'count' integers from the user safely.
 * Uses fgets() + sscanf() to avoid scanf buffer issues.
 */
int getInput(int numbers[]) {
    int count;
    char buffer[1024];  // input buffer

    // Step 1: Ask the number of integers
    printf("Enter how many numbers you want to input (max %d): ", MAX_NUMBERS);

    if (scanf("%d", &count) != 1 || count <= 0 || count > MAX_NUMBERS) {
        printf("Error: Invalid count. Must be between 1 and %d.\n", MAX_NUMBERS);
        exit(1);
    }

    // Clear leftover newline after count
    getchar();

    // Step 2: Ask user to enter exactly 'count' numbers
    printf("Enter %d integers separated by space:\n", count);

    // Read entire line of numbers
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error: Failed to read input.\n");
        exit(1);
    }

    // Step 3: Tokenize the input string and extract integers
    char *token = strtok(buffer, " \t\n");
    int i = 0;
    while (token != NULL && i < count) {
        if (sscanf(token, "%d", &numbers[i]) != 1) {
            printf("Error: Invalid input (only integers allowed).\n");
            exit(1);
        }
        i++;
        token = strtok(NULL, " \t\n");
    }

    if (i < count) {
        printf("Error: You entered fewer numbers than expected.\n");
        exit(1);
    }
    if (token != NULL) {
        printf("Warning: Extra numbers ignored beyond %d.\n", count);
    }

    return count;
}

/* Function: calculateMean */
double calculateMean(int numbers[], int count) {
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return sum / count;
}

/* Function: calculateStdDev */
double calculateStdDev(int numbers[], int count, double mean) {
    double variance = 0.0;
    for (int i = 0; i < count; i++) {
        variance += pow(numbers[i] - mean, 2);
    }
    variance /= count;
    return sqrt(variance);
}

/* ----- MAIN PROGRAM ----- */
int main() {
    int numbers[MAX_NUMBERS];

    int count = getInput(numbers);
    double mean = calculateMean(numbers, count);
    double stddev = calculateStdDev(numbers, count, mean);

    printf("\nResults:\n");
    printf("Count: %d\n", count);
    printf("Mean: %.2f\n", mean);
    printf("Standard Deviation: %.2f\n", stddev);

    return 0;
}
