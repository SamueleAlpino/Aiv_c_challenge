CC=clang
CFLAGS= -Wall -O3 -Wno-pragma-pack -ID:\Program(x86)\GitHub\Aiv_c_challenge\SDL2\include -ID:\Program(x86)\GitHub\Aiv_c_challenge\stb-master 
LDFLAGS= -lSDL2 
BINARY= challenge
BINARY_TESTS=challenge_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

challenge: main.c clock.c
	$(CC) -o $(BINARY) $(LDFLAGS) $^
	
main.o: main.c 
	$(CC) -c -o $@ $(CFLAGS) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^

clock.o: clock.c
	$(CC) -c -o $@ $(CFLAGS) $^

#add challenge.o
test: tests.o 
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o challenge