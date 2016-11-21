# This is the Makefile for Group 53's Asst2 project. This
# program uses our custom-made mymalloc library.
# Typing 'make' or 'make memgrind' will create the executable file.
#

# first we define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#	-pedantic will be necessary as the TAs seem to use it

CC = gcc
CFLAGS  = -g -Wall


# build an executable named memgrind from memgrind.c and mymalloc.c
default: clean worker procs thread

# Create the process worker executable
worker:
	$(CC) $(CFLAGS) -o compressR_worker_LOLS compressR_worker_LOLS.c

# Create the process-oriented program executable
procs:
	$(CC) $(CFLAGS) -o procs compressR_LOLS.c

# Create the process-oriented program executable
thread:
	$(CC) $(CFLAGS) -o thread compressT_LOLS.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
clean:
	$(RM) thread procs compressR_worker_LOLS *.o *~
