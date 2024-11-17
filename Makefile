all:
	gcc src/main.c -o main.o -lncurses

clean:
	rm ./**/*.c-E ./**/*.h-E ./**/*.o ./**/*.exe

run:
	./main.o
