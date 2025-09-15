/*Problem Statement:
Write a C program that implements a basic Binary Search Tree (BST) with functionality to insert integers, search for a value,
delete a node, and display the tree in-order.
Requirements:
• Use defensive programming principles:
o Check for memory allocation errors and invalid operations (e.g., deleting from an empty tree, searching for
non-existent values).
o Organize code into well-defined functions (insert, search, delete, display).
• Include detailed comments on error detection and handling.
• Summarize (in 100-150 words) how your design and error management prevent crashes and improper tree operations.*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ----- BST NODE STRUCTURE ----- */
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

/* ----- FUNCTION DECLARATIONS ----- */
Node* createNode(int value);
Node* insert(Node* root, int value);
Node* search(Node* root, int value);
Node* deleteNode(Node* root, int value);
Node* findMin(Node* root);
void inorder(Node* root);

/* ----- CREATE NEW NODE ----- */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {  // defensive check: memory allocation
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* ----- INSERT INTO BST ----- */
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);  // base case
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Warning: Duplicate value %d ignored.\n", value);//defensive programming
    }
    return root;
}

/* ----- SEARCH IN BST ----- */
Node* search(Node* root, int value) {
    if (root == NULL) {
        return NULL;  // not found
    }
    if (root->data == value) {
        return root;
    } else if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

/* ----- FIND MINIMUM NODE (Helper for deletion) ----- */
Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

/* ----- DELETE NODE FROM BST ----- */
Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        printf("Error: Cannot delete %d (not found).\n", value);
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Found the node to delete
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;  // leaf node
        } else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* temp = findMin(root->right);  // inorder successor
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

/* ----- INORDER TRAVERSAL (sorted order) ----- */
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* ----- MAIN PROGRAM WITH MENU ----- */
int main() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n--- Binary Search Tree Menu ---\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Display (In-order)\n5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1: // Insert
                printf("Enter value to insert: ");
                if (scanf("%d", &value) == 1) {
                    root = insert(root, value);
                } else {
                    printf("Error: Invalid integer.\n");
                    exit(1);
                }
                break;

            case 2: // Search
                printf("Enter value to search: ");
                if (scanf("%d", &value) == 1) {
                    Node* found = search(root, value);
                    if (found) printf("Value %d found in BST.\n", value);
                    else printf("Value %d not found.\n", value);
                } else {
                    printf("Error: Invalid integer.\n");
                    exit(1);
                }
                break;

            case 3: // Delete
                printf("Enter value to delete: ");
                if (scanf("%d", &value) == 1) {
                    root = deleteNode(root, value);
                } else {
                    printf("Error: Invalid integer.\n");
                    exit(1);
                }
                break;

            case 4: // Display
                if (root == NULL) {
                    printf("BST is empty.\n");
                } else {
                    printf("In-order traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 5: // Exit
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Error: Invalid choice.\n");
        }
    }
    return 0;
}

