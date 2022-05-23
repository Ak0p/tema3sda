build: main.c tarb.c tarb.h
	gcc -o tema3 main.c tarb.c tarb.h

run: tema3
	./tema3

clean: tema3
	rm -f tema3
