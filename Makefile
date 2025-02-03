gcal: gcal.o reminder.o interact.o linked_list.o
    gcc -g -o gcal gcal.o reminder.o interact.o linked_list.o

gcal.o: gcal.c reminder.h interact.h
    gcc -g -c gcal.c

# Build the object file for reminder.c
reminder.o: reminder.c reminder.h linked_list.h
    gcc -g -c reminder.c

# Build the object file for interact.c
interact.o: interact.c interact.h linked_list.h
    gcc -g -c interact.c

# Build the object file for linked_list.c
linked_list.o: linked_list.c linked_list.h
    gcc -g -c linked_list.c

# Clean up object files and the executable
clean:
    rm -f *.o gcal