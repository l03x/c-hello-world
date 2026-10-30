CC=gcc
FLAGS=-Wall -Wextra

main: main.c
	$(CC) $(FLAGS) -o main main.c

clean:
	rm main