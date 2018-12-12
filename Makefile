CC=clang
CFLAGS= -O3 -Wno-pragma-pack -I SDL2/include 
LDFLAGS= -lSDL2 -L SDL2/lib/x64
BINARY= challenge
BINARY_TESTS=challenge_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

challenge: main.o clock.o context.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c 
	$(CC) -c -o $@ $(CFLAGS) $^

clock.o: clock.c clock.h
	$(CC) -c -o $@ $(CFLAGS) $<

context.o: context.c context.h 
	$(CC) -c -o $@ $(CFLAGS) $<

tests.o: tests.c 
	$(CC) -c -o $@ $(CFLAGS) $^

test: tests.o context.o clock.o 
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o challenge