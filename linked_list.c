#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Adds a new node with the specified reminder to the front of the list
void addNode(struct LinkedList* list, const char* reminder) {
    // Allocate memory for the new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->reminder, reminder); // Copy the reminder text into the new node
    newNode->next = NULL; // The new node will be the last node, so next is NULL

    // If the list is empty, set the new node as the head
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // Traverse the list to find the last node
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Set the next of the last node to the new node
        current->next = newNode;
    }
}


// Deletes all nodes in the list and frees allocated memory
void deleteList(struct LinkedList* list) {
    struct Node* current = list->head;
    // Iterates through the list
    while (current) {
        struct Node* temp = current;
        current = current->next; // Moves to the next node
        free(temp); // Frees memory for the current node
    }
    // Sets the head to NULL to indicate the list is empty
    list->head = NULL;
}

// Prints all reminders in the list
void printList(struct LinkedList* list) {
    struct Node* current = list->head;
    // Iterates through the lis
    while (current) {
        printf("  - %s\n", current->reminder); // Prints the reminder
        current = current->next; // Moves to the next node
    }
}
