/*Design and implement a C program to manage a simple library system. The program should allow the user to:
• Add new books (with title, author, ISBN).
• Search for a book by title.
• Display all available books.*/
/*
 * Library Management System in C (using scanf instead of fgets)
 * Features:
 *   - Add new books (title, author, ISBN)
 *   - Search for a book by title
 *   - Display all available books
 *
 * Program uses:
 *   - Structures (for book representation)
 *   - Functions (for modular programming)
 *   - Arrays (to store multiple books)
 */

#include <stdio.h>   // Standard Input/Output library
#include <string.h>  // For string comparison (strcmp)

/* ----- CONSTANTS ----- */
#define MAX_BOOKS 100     // Maximum number of books that can be stored
#define TITLE_LEN 100     // Maximum length of book title
#define AUTHOR_LEN 100    // Maximum length of author name
#define ISBN_LEN 20       // Maximum length of ISBN

/* ----- STRUCTURE DEFINITION ----- */
/* Book structure stores information of a single book */
typedef struct {
    char title[TITLE_LEN];   // Title of the book
    char author[AUTHOR_LEN]; // Author of the book
    char isbn[ISBN_LEN];     // ISBN number of the book
} Book;

/* ----- FUNCTION DECLARATIONS ----- */
/* These are prototypes (declarations) for functions defined later */
void addBook(Book books[], int *count);     // Adds a new book to the library
void searchBook(Book books[], int count);   // Searches for a book by title
void displayBooks(Book books[], int count); // Displays all available books

/* ----- FUNCTION DEFINITIONS ----- */

/*
 * Function: addBook
 * -----------------
 * Adds a new book to the collection if space is available.
 * Parameters:
 *   books[]: Array that stores all books
 *   count: Pointer to number of books currently stored
 */
void addBook(Book books[], int *count) {
    // Check if library is already full
    if (*count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    // Take book details from the user
    printf("Enter Title: ");
    scanf(" %[^\n]s", books[*count].title);   // Reads full string including spaces

    printf("Enter Author: ");
    scanf(" %[^\n]s", books[*count].author);

    printf("Enter ISBN: ");
    scanf(" %[^\n]s", books[*count].isbn);

    // Increment total book count after successful entry
    (*count)++;
    printf("Book added successfully!\n");
}

/*
 * Function: searchBook
 * --------------------
 * Searches for a book by title in the collection.
 * Parameters:
 *   books[]: Array of books
 *   count: Total number of books stored
 */
void searchBook(Book books[], int count) {
    char title[TITLE_LEN]; // To store title input for searching

    printf("Enter title to search: ");
    scanf(" %[^\n]s", title);  // Read the search string including spaces

    // Loop through all books to find a match
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0) {  // Compare input title with stored titles
            printf("\nBook Found:\nTitle: %s\nAuthor: %s\nISBN: %s\n",
                   books[i].title, books[i].author, books[i].isbn);
            return; // Exit function once book is found
        }
    }

    // If loop ends without finding a match
    printf("Book not found.\n");
}

/*
 * Function: displayBooks
 * ----------------------
 * Displays all books currently in the library.
 * Parameters:
 *   books[]: Array of books
 *   count: Total number of books stored
 */
void displayBooks(Book books[], int count) {
    // If no books are stored
    if (count == 0) {
        printf("No books available.\n");
        return;
    }

    // Print all books in formatted style
    printf("\nAvailable Books:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Title: %s | Author: %s | ISBN: %s\n",
               i + 1, books[i].title, books[i].author, books[i].isbn);
    }
}

/*
 * Function: main
 * --------------
 * Entry point of the program.
 * Provides a menu-driven interface to the user.
 */
int main() {
    Book books[MAX_BOOKS];  // Array to store all books
    int count = 0;          // Current number of books
    int choice;             // Menu choice variable

    do {
        // Display menu options to the user
        printf("\n====== Library Menu ======\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Display Books\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice); // Take user's choice

        // Perform action based on user choice
        switch (choice) {
            case 1: addBook(books, &count); break;       // Add a book
            case 2: searchBook(books, count); break;     // Search for a book
            case 3: displayBooks(books, count); break;   // Display all books
            case 4: printf("Exiting program.\n"); break; // Exit option
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4); // Continue until user chooses "Exit"

    return 0; // Successful program termination
}
