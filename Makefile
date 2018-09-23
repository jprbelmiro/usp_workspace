all:
	@gcc *.c -o main -Wall -lm -I.
	
run:
	@./main

debug:
	@gcc *.c -o main -O3 -Wall -I. -v -g -lm
	@valgrind --leak-check=full --show-leak-kinds=all -v ./main
