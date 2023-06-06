make: clean library test

library:
	cp -r src/nox lib

test: build run

build:
	g++ src/*.cpp -o bin/exe -Ilib

run:
	./bin/exe

clean:
	rm -rf lib/* bin/*