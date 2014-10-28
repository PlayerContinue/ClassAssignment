#Name: David Greenberg
#Lab # 5
#Lab-Name: Paging


#Executable information and src and objects
EXECUTABLES = paging
SRC = paging.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -g -pthread -lrt

#Occur in all cases
all:$(EXECUTABLES)

$(EXECUTABLES):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

paging:$(EXECUTABLES)

#Remove all .o and executable files
clean:
	rm -f $(EXECUTABLES) $(OBJ) *~
