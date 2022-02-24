CC=gcc
CFLAGS=-I. -lm -O3
DEPS = timer.h linkedList.h minHeap.h
OBJ = timer.o linkedList.o minHeap.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -fopenmp

djikstra: $(OBJ) djikstra.o
	$(CC) -fopenmp -o $@ $^ $(CFLAGS)

clean:
	\rm -f *.o djikstra *.exe *~ *#