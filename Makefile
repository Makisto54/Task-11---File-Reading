.PHONY: clean

main: main.c
	gcc main.c -o main -g  

clean:
	rm main