srv: *.c
	@gcc server.c -o srv -Wall -lm -I.

clt: *.c
	@gcc client.c -o clt -Wall -lm -I.

runsrv:
	@./srv

runclt:
	@./clt


debugsrv:
	@gcc server.c -o srv -O3 -Wall -I. -v -g -lm
	@valgrind --leak-check=full --show-leak-kinds=all -v ./srv

debugclt:
	@gcc client.c -o clt -O3 -Wall -I. -v -g -lm
	@valgrind --leak-check=full --show-leak-kinds=all -v ./clt
