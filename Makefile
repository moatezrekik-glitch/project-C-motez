CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

SRC = src/main.c src/catalogue.c src/pile.c src/file.c src/bst.c
OBJ = $(SRC:.c=.o)
EXEC = bibliotheque

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)