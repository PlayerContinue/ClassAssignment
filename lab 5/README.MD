    ___            __ _     _              __ _  
   | _ \  __ _    / _` |   (_)    _ _     / _` | 
   |  _/ / _` |   \__, |   | |   | ' \    \__, | 
  _|_|_  \__,_|   |___/   _|_|_  |_||_|   |___/  
_| """ |_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| 
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' 
--------------------------------------------------
Usage
	1) Compile the program using make paging/all. 
	2) Run the program with paging # 
		(# is a numerical value between 0 2^32)

Makefile
	all: Compiles paging.c into the executable paging, also include intermediary step to paging.o
	paging: Compiles paging.c into the executable paging, also include intermediary step to paging.o
	clean: Removes all .o and executable files with the name paging

--------------------------------------------------
Version 1.0 
	