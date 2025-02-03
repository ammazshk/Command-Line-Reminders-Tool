#include "reminder.h"
#include "interact.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Signal handler to handle interrupts, save reminders, and exit
void signalHandler(int signal) {
    printf("\nProgram interrupted...\n");
    printf("Writing to file...\n");
    writeToFile(); // Save reminders to file
    exit(signal); // Exit the program with the received signal
}

// Returns the current day as an integer
int getCurrentDay(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_mday;
}

// Returns the name of the month based on its index
const char* getMonth(int monthIndex) {
    static const char* monthNames[] = {
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"
    };
    return monthNames[monthIndex];
}

// Returns the day name (Sun, Mon, Tue, etc.) for a given start day and target date
const char* getDay(int startDay, int targetDate) {
    static const char* daysOfWeek[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    
    int dayIndex = (startDay + targetDate) % 7; // Calculate the day of the week
    return daysOfWeek[dayIndex];
}


// Removes a reminder at the given index for a specific day
void removeReminder(int day, int index) {
    // Check for valid date 
    if (day < 1 || day > month.month_days) {
        printf("Invalid day: must be between 1 and %d.\n", month.month_days);
        return;
    }

    // Get the reminder list for the day
    struct LinkedList *list = month.reminders[day - 1];
     // Check if there are no reminders
    if (!list->head) {
        printf("No reminders for day %d.\n", day);
        return;
    }

    // Defining current and previous nodes and count
    struct Node *current = list->head;
    struct Node *previous = NULL;
    int count = 1;

    // Traverse the linked list to find the reminder at the given index
    while (current && count < index) {
        previous = current;
        current = current->next;
        count++;
    }

    // If the reminder is found, remove it from the list
    if (current && count == index) {
        if (previous) {
            previous->next = current->next;
        } else {
            list->head = current->next; // Removing the head node
        }
        free(current);
    } else {
        printf("Invalid index: No reminder at position %d for day %d.\n", index, day);
    }
}

// Checks if the input is a valid integer
int check_integer(const char *input) {
    int x;
    // Try to read an integer from input
    if (sscanf(input, "%d", &x) == 1) {
        return 1;  // It's an integer
    }
    return 0;  // Not an integer
}


int main(int argc, char *argv[]) {
    // Register signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    initializeMonth(); // Initialize month details
    readFromFile();    // Load reminders from file

    // Check if user is trying to add or remove reminders and validate arguments
    if ((strcmp(argv[1], "add") == 0 || strcmp(argv[1], "remove") == 0) && argc >= 4) {
        if (check_integer(argv[2]) == 0) {
            printf("Invalid day\n");
            return 1;
        }
    } 
    
    // Validate arguments for view or today commands
    if ((strcmp(argv[1], "view") == 0 || strcmp(argv[1], "today") == 0) && argc < 2) {
        printf("%d", argc);
        printf("Invalid arguments\n");
        printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
        return 1;
    }

    // Add a reminder for a specific day
    if (strcmp(argv[1], "add") == 0 && argc >= 4) {
        int day = atoi(argv[2]); // Convert day argument to integer
        char reminder[MAX_STR_LEN] = "";
        // Combine reminder words into a single string
        for (int i = 3; i < argc; i++) {
            strcat(reminder, argv[i]);
            if (i < argc - 1) strcat(reminder, " ");
        }
        insertToCalendar(day, reminder); // Insert reminder to the calendar
        printCalendar();  // Print updated calendar

    // Remove a reminder for a specific day and index
    } else if (strcmp(argv[1], "remove") == 0 && argc == 4) {
        int day = atoi(argv[2]);
        int index = atoi(argv[3]);
        removeReminder(day, index); // Remove reminder from the calendar
        printCalendar(); // Print updated calendar

    // View all reminders for the current month
    } else if (strcmp(argv[1], "view") == 0) {
        printCalendar();

    // Show reminders for today
    } else if (strcmp(argv[1], "today") == 0) {
        int today = getCurrentDay();  // Get the current day
        const char* monthName = getMonth(month.month_idx); // Get the month name
        const char* dayName = getDayName(month.start_day, today); // Get the day of the week

        printf("Reminders for %s %d:\n", monthName, today);  // Print day name and date
        struct LinkedList *list = month.reminders[today - 1];  // Get the reminder list for the current day

        // Check if there are reminders
        if (list->head != NULL) {
            struct Node* current = list->head;  // Start with the first reminder
            int count = 1; 

            // Print first reminder
            printf("%s %2d:: (%d) %s\n", dayName, today, count, current->reminder);
            current = current->next; 
            count++; 

            // Iterate through the linked list and print reminders in the desired format
            while (current) {
                printf("         (%d) %s\n", count, current->reminder); 
                current = current->next;
                count++;
            }
        } else {
            printf("No reminders for today.\n");  // Handle the case where there are no reminders
        }

    }
    else {
        printf("Invalid arguments\n");
        printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
    }

    writeToFile(); // Save reminders before exiting
    return 0;
}
