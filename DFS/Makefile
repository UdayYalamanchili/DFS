EXEC = assignment7
CPP = g++
CFLAGS = -c -Wall

assignment7: Assignment7.o
	${CPP} -o ${EXEC} Assignment7.o

assignment7.o: Assignment7.cpp
	${CPP} ${CFLAGS} Assignment7.cpp

clean:
	rm *.o ${EXEC}
