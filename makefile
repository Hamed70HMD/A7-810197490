CC = g++ -std=c++11

a.out: main.o User.o Film.o Comment.o
	$(CC) main.o User.o Film.o Comment.o -o a.out

main.o: main.cpp User.o Film.o Comment.o
	$(CC) -c main.cpp

User.o: User.cpp User.h
	$(CC) -c User.cpp

Film.o: Film.cpp Film.h
	$(CC) -c Film.cpp

Comment.o: Comment.cpp Comment.h
	$(CC) -c Comment.cpp

.PHONY: clean

clean:
	rm *.o
