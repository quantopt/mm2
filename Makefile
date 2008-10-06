CARGS = -g -ggdb -Wall -pthread -lm -fpic -O3
CC = gcc

all: clean match

match:
	$(CC) $(CARGS) directsolve.c optics.c transforms.c pso1d.c randvar.c

direct: clean
	$(CC) $(CARGS) -o match directsolve.c optics.c transforms.c 

optics.so: 
	$(CC) $(CARGS) -L. -loptics -o match

.c:
	$(CC) $(CARGS) -o $@ $@.c


.o: 
	$(CC) -fpic -c $@.c
	
.PHONY: clean

clean:
	rm -f *.o match
