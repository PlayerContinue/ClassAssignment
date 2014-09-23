#Name: David Greenberg
#Lab # 3
#Lab-Name: Catcher

#Executable information and src and objects
EXECUTABLES = catcher
SRC = catcher.c
OBJ = ($SRC:.c=.o)

CC = gcc
CFLAGS = -g 

#Occur in all cases
all: $(EXECUTABLES)

$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

catcher:

#Remove all .o and executable files
clean:
	rm -f $(EXECUTABLES) $(OBJ) *~ 
	
	

