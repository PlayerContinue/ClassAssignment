#Name: David Greenberg
#Lab # 4
#Lab-Name: Rice And Rice And Rice And Rice

#Executable information and src and objects
EXECUTABLES = dining-p
SRC = dining-p.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -g -pthread -lrt

#Occur in all cases
all:$(EXECUTABLES)

$(EXECUTABLES):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

dining-p:$(EXECUTABLES)

#Remove all .o and executable files
clean:
	rm -f $(EXECUTABLES) $(OBJ) *~

test:
	make && ./launch-philosophers 2 2

test2:
	make && ./launch-philosophers 3 3
