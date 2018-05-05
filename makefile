CC=gcc

main.o : main.c
	$(CC) -pthread main.c -o main

clean:
	rm -f main
