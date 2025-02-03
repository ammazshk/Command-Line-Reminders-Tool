#include "reminder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global variable to store current month information
struct Month month;

// Initializes the current month's details
void initializeMonth(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    month.month_idx = t->tm_mon;

    t->tm_mday = 1;
    mktime(t);
    month.start_day = t->tm_wday;

    month.month_days = t->tm_mday;
    // Loop through each day of the current month to determine the total number of days
    while (t->tm_mon == month.month_idx) {
        month.month_days = t->tm_mday;
        t->tm_mday++;
        mktime(t);
    }

    // Initialize reminder lists for each day
    for (int i = 0; i < 31; i++) {
        month.reminders[i] = (struct LinkedList*)malloc(sizeof(struct LinkedList));
        month.reminders[i]->head = NULL;
    }
}

// Inserts a reminder for a specific day in the calendar
void insertToCalendar(int day, const char* value) {
    // Check if the day is within the valid range
    if (day < 1 || day > month.month_days) {
        printf("Invalid day: The day must be >= 1 and <= %d\n", month.month_days);
        return;
    }
    // Add the reminder to the corresponding day
    addNode(month.reminders[day - 1], value);
}

// Returns the name of the month based on its index
const char* getMonthName(int monthIndex) {
    static const char* monthNames[] = {
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"
    };
    return monthNames[monthIndex];
}

// Returns the day name (Sun, Mon, Tue, etc.) for a given start day and target date
const char* getDayName(int startDay, int targetDate) {
    static const char* daysOfWeek[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    
    int dayIndex = (startDay + targetDate) % 7; // Calculate the day of the week
    return daysOfWeek[dayIndex];
}

// Prints the calendar with reminders for the month
void printCalendar(void) {
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    int day = 1;

    printf(" ");
    // Print the days of the week for the first week
    for (int i = 1; i <= 7; i++) {
        if (i < month.start_day) {
            printf("     ");
        } else {
            // Print the day number with a reminder if available
            if (month.reminders[day - 1]->head) {
                printf("(%2d) ", day);
            } else {
                printf(" %2d  ", day);
            }
            day++;
        }
    }
    printf("\n");

    // Print the rest of the days for the month
    while (day <= month.month_days) {
        for (int i = 1; i <= 7; i++) {
            if (day > month.month_days) {
                break; // Stop printing when the month end
            }
            if (i==1) {
                printf(" ");
            }
            // Print the day number with a reminder if available
            if (month.reminders[day - 1]->head) {
                printf("(%2d) ", day);
            } else {
                printf(" %2d  ", day);
            }
            day++;
        }
        printf("\n");
    }
    printf("\n");

    // Print the reminders for the month
    printf("%s reminders:\n", getMonthName(month.month_idx));
    for (int i = 0; i < month.month_days; i++) {
        // Print reminders if they exist for the day
        if (month.reminders[i]->head) {
            printf("%s %2d:: ", getDayName(month.start_day, i), i+1);
            struct Node* current = month.reminders[i]->head;
            int count = 1;
            // Print each reminder for the day
            while (current) {
                if (current == month.reminders[i]->head) {
                    printf("(%d) %s\n", count, current->reminder);
                } else if (i + 1 < 10) {
                    printf("        (%d) %s\n", count, current->reminder);
                } else {
                    printf("         (%d) %s\n", count, current->reminder);
                }
                current = current->next;
                count++;
            }
        }
    }
    printf("____________________________\n");
}
