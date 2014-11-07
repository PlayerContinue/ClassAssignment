#Name: David Greenberg
#Lab # 6
#Lab-Name: Deamon


#Executable information and src and objects
EXECUTABLES = sprintd mole
SRC = sprintd.c mole.c 
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -g

#Occur in all cases
all:$(EXECUTABLES)

$(EXECUTABLES):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

#Compile sprintd
sprintd:SRC=sprintd.c

#Compile mole
mole:SRC=mole.c

#Remove all .o and executable files
clean:
	rm -f $(EXECUTABLES) $(OBJ) sprintd.o mole.o *~
