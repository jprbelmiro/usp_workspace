all:
	@g++ *.cpp -o main -Wall -lm -I.
	
run:
	@./main

debug:
	@g++ *.cpp -o main -O3 -Wall -I./include -v -g -lm
	@valgrind --leak-check=full --show-leak-kinds=all -v ./main
