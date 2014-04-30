all:
	gcc -O2 -I/usr/X11/include/ -L/usr/lib/ -L/usr/X11R6/lib -lX11 -lm tspShow.c enumTsp.c -o tspShow.out
	./tspShow.out -n tsp-test2
