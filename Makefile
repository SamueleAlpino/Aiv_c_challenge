CC=clang
CPPCHECK=cppcheck
CFLAGS= -Wall -Werror -O3 -I D:\Program(x86)\GitHub\Aiv_c_challenge\SDL2\include -Wno-pragma-pack
LDFLAGS=-lSDL2 
BINARY=challenge
BINARY_TESTS=challenge_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

challenge: main.o challenge.o gfx.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^
	
main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^

#add challenge.o
test: tests.o 
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o tetris