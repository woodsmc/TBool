CC      = g++ -std=c++11

all: example clean

example: main.o
	$(CC) $^ -o $@

main.o: main.cpp tbool.h
	$(CC) -c $<

clean:
	rm *.o

reallyclean:
	rm *.o example