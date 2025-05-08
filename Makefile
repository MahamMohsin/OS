math_solver: main.o math.o
	gcc main.o math.o -o math_solver

main.o: main.c
	gcc -c main.c

math.o: math.c math.h
	gcc -c math.c

clean: rm* .o math_solver
