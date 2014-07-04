all:
	gcc -O2 tspShow.c enumTsp.c -o tspShow.out
	./tspShow.out -n samples/tsp-test
