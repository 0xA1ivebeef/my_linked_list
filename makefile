
CC = gcc
CFLAGS = -Wall -Wextra

make:
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm main
