CC = g++ -std=c++11

a.out: main.o User.o Film.o
	$(CC) main.o User.o Film.o -o a.out

main.o: main.cpp User.o Film.o
	$(CC) -c main.cpp

User.o: User.cpp User.h
	$(CC) -c User.cpp

Film.o: Film.cpp Film.h
	$(CC) -c Film.cpp

.PHONY: clean

clean:
	rm *.o
