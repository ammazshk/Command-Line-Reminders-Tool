#ifndef REMINDER_H
#define REMINDER_H

#include <stdbool.h>
#include "linked_list.h"

#define MAX_STR_LEN 100

// File name to save/load reminders
#define FILE_NAME "reminders.txt"

struct Month {
    int month_days; // Number of days in the month
    int start_day; // Starting day of the month
    int month_idx; // Month index (0 = January)
    struct LinkedList* reminders[31]; // Reminders for each day (1-31)
};

// Extern declaration of month
extern struct Month month;

// Initialize month (days, start day)
void initializeMonth(void);

// Add a reminder for a specific day
void insertToCalendar(int day, const char* value);

// Print all reminders for the month
void printCalendar(void);

// Get month name by index
const char* getMonthName(int monthIndex);

// Get day name for a given date
const char* getDayName(int startDay, int targetDate);

#endif
