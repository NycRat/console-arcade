all:
	gcc -std=c17 -o main.o ./src/main.c

clean:
	rm ./main.o
