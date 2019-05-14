CC = g++ -std=c++11

a.out: main.o
	$(CC) main.o -o a.out

main.o: main.cpp
	$(CC) -c main.cpp

.PHONY: clean

clean:
	rm *.o
