#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define TABLE_SIZE 10 // Define the size of the hash table 
 
// Node structure for the linked list (used for separate chaining) 
struct Node { 
    char name[50]; // Name field 
 
 
    struct Node* next; 
}; 
 
// Hash table array of pointers to Node 
struct Node* hashTable[TABLE_SIZE]; 
 
// Hash function 
int hashFunction(char* name) { 
    int hash = 0; 
    for (int i = 0; name[i] != '\0'; i++) { 
        hash += name[i]; 
    } 
    return hash % TABLE_SIZE; 
} 
 
// Insert a name into the hash table 
void insert(char* name) { 
    int index = hashFunction(name); 
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
    strcpy(newNode->name, name); 
    newNode->next = NULL; 
 
    if (hashTable[index] == NULL) { 
        hashTable[index] = newNode; // Insert directly if no collision 
    } else { 
        struct Node* temp = hashTable[index]; 
        while (temp->next != NULL) { 
            temp = temp->next; // Traverse to the end of the list 
        } 
        temp->next = newNode; // Add new node at the end 
    } 
    printf("Inserted: %s\n", name); 
 
 
} 
 
// Search for a name in the hash table 
void search(char* name) { 
    int index = hashFunction(name); 
    struct Node* temp = hashTable[index]; 
 
    while (temp != NULL) { 
        if (strcmp(temp->name, name) == 0) { 
            printf("Name found: %s\n", name); 
            return; 
        } 
        temp = temp->next; 
    } 
    printf("Name not found: %s\n", name); 
} 
 
// Display the contents of the hash table 
void display() { 
    for (int i = 0; i < TABLE_SIZE; i++) { 
        printf("Index %d: ", i); 
        struct Node* temp = hashTable[i]; 
        if (temp == NULL) { 
            printf("NULL"); 
        } else { 
            while (temp != NULL) { 
                printf("%s -> ", temp->name); 
                temp = temp->next; 
            } 
        } 
        printf("NULL\n"); 
    } 
 
 
} 
 
int main() { 
    // Initialize the hash table to NULL 
    for (int i = 0; i < TABLE_SIZE; i++) { 
        hashTable[i] = NULL; 
    } 
 
    int choice; 
    char name[50]; 
 
    do { 
        printf("\nMenu:\n"); 
        printf("1. Insert Name\n"); 
        printf("2. Search Name\n"); 
        printf("3. Display Hash Table\n"); 
        printf("4. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: 
                printf("Enter name to insert: "); 
                scanf("%s", name); 
                insert(name); 
                break; 
            case 2: 
                printf("Enter name to search: "); 
                scanf("%s", name); 
                search(name); 
                break; 
            case 3: 
 
 
                display(); 
                break; 
            case 4: 
                printf("Exiting...\n"); 
                break; 
            default: 
                printf("Invalid choice! Please try again.\n"); 
        } 
    } while (choice != 4); 
 
    return 0; 
}