#ifndef INTERACT_H
#define INTERACT_H

#include <stdio.h>
#include "reminder.h"  // Reminder functions and structures

// Reads a reminder from input and stores it in str (max size n)
int readReminder(char* str, int n);

// Flushes the input buffer
void flushBuffer(void);

// Reads reminder data from a file
void readFromFile(void);

// Writes reminder data to a file
void writeToFile(void);

#endif
