#include "interact.h"
#include <string.h>

// Reads a reminder for a specific day and stores it in str which has a max size n characters
int readReminder(char* str, int n) {
    int day;

    // Ask user to enter day and reminder
    printf("Enter day and reminder (0 to quit): ");
    // Check fort valid input
    if (scanf("%d", &day) != 1) {
        flushBuffer();
        printf("Invalid input. Please enter a valid day and reminder.\n");
        return -1;
    }

    if (day == 0) {
        return 0;
    }

    // Check for invalid day
    if (day < 1 || day > month.month_days) {
        printf("Invalid day: The day must be >= 1 and <= %d\n", month.month_days);
        return -1;
    }

    // Gets reminder and assigns it to str
    fgets(str, n, stdin);
    // removes \n frtom str
    str[strlen(str) - 1] = '\0';
    
    return day;
}

// Flushes the input buffer to clear extra characters
void flushBuffer(void) {
    int c;
    while (1) {
        c = getchar(); 
        // Reads characters until newline or EOF
        if (c == '\n' || c == EOF) {
            break;
        }
    }
}

// Writes reminders to a file
void writeToFile(void) {
    FILE* file = fopen(FILE_NAME, "w"); // Opens the file in write mode
    for (int i = 0; i < month.month_days; i++) {
        struct Node* current = month.reminders[i]->head;
        // Iterates through reminders for each day
        while (current) {
            // Writes day and reminder to file
            fprintf(file, "%d,%s\n", i + 1, current->reminder);
            current = current->next;
        }
    }
    fclose(file); // Closes the file
}

// Reads reminders from a file and adds them to the list
void readFromFile(void) {
    FILE* file = fopen(FILE_NAME, "r"); // Opens the file in read mode
    // Checks if reminders text file already exists
    if (!file) {
        printf("No reminders file\n");
        return;
    }

    char line[MAX_STR_LEN];
    // Reads each line from file
    while (fgets(line, sizeof(line), file)) {
        int day;
        char reminder[MAX_STR_LEN];
        // Deals with day and reminder values from file
        if (sscanf(line, "%d,%[^\n]", &day, reminder) == 2) {
            addNode(month.reminders[day - 1], reminder); // Adds reminder to list
        }
    }
    fclose(file); // Closes file
}
