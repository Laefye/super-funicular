CC=clang
CFLAGS=-Wall -DEXPORT
LDFLAGS=

all: logicarrows.dll

src/chunk.o: src/chunk.c # not work
	$(CC) $(CFLAGS) -c $^ -o $@

src/game.o: src/game.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f src/main.o
	rm -f src/chunk.o
	rm -f src/game.o
	rm -f logicarrows.dll
	rm -f logicarrows.exp
	rm -f logicarrows.lib

logicarrows.dll: src/game.o
	$(CC) -shared $(LDFLAGS) $^ -o $@