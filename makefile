CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
LIBS = -lm

TEST_TARGET = unit_tests

OBJ_TEST = testepoligono.o poligono.o

all: test

test: $(OBJ_TEST)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(OBJ_TEST) $(LIBS)
	./$(TEST_TARGET)

%.o: %.c poligono.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TEST_TARGET)