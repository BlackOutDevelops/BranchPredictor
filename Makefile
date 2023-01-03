all:
	gcc -g -o SIM gshare.c -lm ${LIBS}
clean:
	rm *~ *.o SIM
