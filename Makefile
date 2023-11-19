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
	rm -f game/logicarrows.dll
	rm -fr game/__pycache__

logicarrows.dll: src/game.o
	$(CC) -shared $(LDFLAGS) $^ -o $@

run: logicarrows.dll
	cp logicarrows.dll game/logicarrows.dll
	cd game && python main.py