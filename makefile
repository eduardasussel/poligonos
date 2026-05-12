TARGET = siguel
CC = gcc
CFLAGS = -std=c99 -Wall -fstack-protector-all -g
LIBS = -lm

OBJ = main.o \
		comandos.o \
		fila.o \
		forma.o \
		lerGeo.o \
		lerQry.o \
		lista.o \
		poligono.o \
		ponto.o \
		svg.o \

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	mkdir -p saidas
	./$(TARGET) -e entradas -f arq.geo -o saidas -q polig-1-mcs.qry