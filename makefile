make: clean library test

library:
	cp -r src/nox lib

test: build run

build:
	g++ src/*.cpp -o bin/exe -Ilib

run:
	./bin/exe

debug: clean library gen_debug val

gen_debug:
	g++ src/*.cpp -o bin/exe -Ilib -g -O0

val:
	valgrind --leak-check=yes bin/exe

clean:
	rm -rf lib/* bin/*