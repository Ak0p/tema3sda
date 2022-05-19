CC=gcc
CFLAGS=-Wextra -g
OBJ=main.o tarb.o auxarb.o
TARGET=lab8

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) *~

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

