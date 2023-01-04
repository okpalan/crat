CC=gcc

OBJ=./obj
LIB=./lib
INCLUDE=./include

all: vector.o gifenc.o jsonp.o 

vector.o: $(LIB)/vector.c
	$(CC) -c $(LIB)/vector.c -o $(OBJ)/vector.o -I$(INCLUDE)

jsonp.o: $(LIB)/jsonp.c
	$(CC) -c $(LIB)/jsonp.c -o $(OBJ)/jsonp.o -I$(INCLUDE)

gifenc.o: $(LIB)/gifenc.c
	$(CC) -c $(LIB)/gifenc.c -o $(OBJ)/gifenc.o -I$(INCLUDE)

clean:
	rm -f $(OBJ)/*.o

