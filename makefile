all:
	gcc project1.c

s:
	gcc project1.c -g && ./a.out test2.txt

t: 
	gcc project1.c -g && ./a.out

full:
	 gcc createTest.c -o createTest.out && gcc project1.c -g && ./createTest.out && ./a.out test2.txt

test:
	gcc project1.c -g && ./a.out -
