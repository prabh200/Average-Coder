CC = clang++

all: main

main: obj
	$(CC) *.o -o main

obj:
	$(CC) -c *.cpp

clean:
	rm -f main *.o

run:
	./main