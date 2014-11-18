#Name: David Greenberg
#Lab # 7
#Lab-Name: Asynchronous Elephant


#Executable information and src and objects
EXECUTABLES = matrix_add matrix_gen
SRC = matrix_add.c matrix_gen.c 
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -g 

#Occur in all cases
all:$(EXECUTABLES)

$(EXECUTABLES):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -lrt
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lrt

#Compile spiritd
matrix_gen:SRC=matrix_gen.c

#Compile matrix_add
matrix_add:SRC=matrix_add.c

#run a test
test1: 
	make && ./matrix_gen > "hello.txt" && ./matrix_add < ./hello.txt > "hello2.txt"

#Remove all .o and executable files
clean:
	rm -f $(EXECUTABLES) $(OBJ) sprintd.o spirit.o mole.o *~
