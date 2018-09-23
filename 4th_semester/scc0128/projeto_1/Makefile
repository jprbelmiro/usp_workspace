all:
	@g++ noheuristic/*.cpp -o noheuristic/main -Wall -lm -I.
	@g++ heuristic/*.cpp -o heuristic/main -Wall -lm -I.
	
run:
	@./main

debug:
	@g++ *.cpp -o main -O3 -Wall -I./include -v -g -lm
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./main

nhmain:
	@g++ noheuristic/*.cpp -o noheuristic/main -Wall -lm -I.
	@./noheuristic/main

hmain:
	@g++ heuristic/*.cpp -o heuristic/main -Wall -lm -I.
	@./heuristic/main