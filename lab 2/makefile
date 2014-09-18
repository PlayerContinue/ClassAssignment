#name: David Greenberg
#Project: Lab 2
# Project: Launch-Tube


# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.




# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=launch.out
SRC=launch.c
OBJ=launch.o

tube: EXECUTABLE = tube.out
tube: SRC = tube.c
tube: OBJ = tube.out
# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g


# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLES) 

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLES) $(OBJ) *~

all: $(EXECUTABLES)

tube:

launch: 

test:

	gcc ./tube.c -g -o tube.out && ./tube.out /bin/cat ./testdoc.txt , /usr/bin/head -2

test3:
	gcc ./tube.c -g -o tube.out && ./tube.out /bin/ls -l , /usr/bin/head -2
test4: 
	gcc ./tube.c -g -o tube.out && ./tube.out /bin/cat ./makefile , /usr/bin/head -2

test5: 
	gcc ./tube.c -g -o tube.out && ./tube.out head , /bin/ls -l

