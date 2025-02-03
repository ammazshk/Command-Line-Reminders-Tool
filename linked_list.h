#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_STR_LEN 100 // Maximum length for reminder strings

struct Node {
    char reminder[MAX_STR_LEN]; // Text of reminder
    struct Node* next; // Pointer to the next node
};

// LinkedList structure to manage a list of nodes
struct LinkedList {
    struct Node* head;
};

// Adds a new node with the specified reminder to the list
void addNode(struct LinkedList* list, const char* reminder);

// Deletes all nodes in the list and frees memory
void deleteList(struct LinkedList* list);

// Prints all reminders in the list
void printList(struct LinkedList* list);

#endif
