CC = g++ -std=c++11

a.out: main.o Interface.o User.o Film.o Comment.o Notification.o
	$(CC) main.o Interface.o User.o Film.o Comment.o Notification.o -o a.out

main.o: main.cpp User.o Film.o Comment.o Notification.o
	$(CC) -c main.cpp

Interface.o: Interface.cpp Interface.h User.o Film.o Comment.o Notification.o
	$(CC) -c Interface.cpp
 
User.o: User.cpp User.h
	$(CC) -c User.cpp

Film.o: Film.cpp Film.h
	$(CC) -c Film.cpp

Comment.o: Comment.cpp Comment.h
	$(CC) -c Comment.cpp

Notification.o: Notification.cpp Notification.h
	$(CC) -c Notification.cpp

.PHONY: clean

clean:
	rm *.o
