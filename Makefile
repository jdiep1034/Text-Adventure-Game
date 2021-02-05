CFLAGS = -std=c99 -g -O3 -Wall -Wextra -Wno-unused-result -D_POSIX_C_SOURCE=200809L
OBJ = items.o characters.o rooms.o adventure.o 
PROG = adventure

$(PROG): $(OBJ)
				gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)