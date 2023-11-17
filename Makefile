CC=clang
CFLAGS=-Wall
LDFLAGS=

all: game.exe

game.exe: src/main.o src/game.o
	$(CC) $(LDFLAGS) $^ -o game.exe

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^ -o $@

src/chunk.o: src/chunk.c # not work
	$(CC) $(CFLAGS) -c $^ -o $@

src/game.o: src/game.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f src/main.o
	rm -f src/chunk.o
	rm -f src/game.o
	rm -f game.exe
	
run: game.exe
	./game.exe