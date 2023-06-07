make: clean library test

library:
	cp -r src/nox lib

test: build run

build:
	g++ src/*.cpp -o bin/exe -Ilib -std=c++20

run:
	./bin/exe

clean:
	rm -rf lib/* bin/*