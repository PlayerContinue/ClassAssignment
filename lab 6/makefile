#Name: David Greenberg
#Lab # 6
#Lab-Name: Deamon


#Executable information and src and objects
EXECUTABLES = spiritd mole
SRC = spiritd.c mole.c 
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -g

#Occur in all cases
all:$(EXECUTABLES)

$(EXECUTABLES):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

#Compile spiritd
spiritd:SRC=spiritd.c

#Compile mole
mole:SRC=mole.c

#Remove all .o and executable files
clean:
	rm -f $(EXECUTABLES) $(OBJ) sprintd.o spirit.o mole.o *~
