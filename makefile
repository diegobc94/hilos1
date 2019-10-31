main: main.o
	gcc -o main main.c

main.o: main.c
	gcc -c main.c

.PHONY:
clean:
	rm -rf *.o
	rm main