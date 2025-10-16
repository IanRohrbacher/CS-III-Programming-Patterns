# file to build
buildfile = CoffeeShack.cpp

# compiled
compiledfile = coffee

# compiler flags
compiler = g++
flags = -std=c++17

# default target
all: run

# targets
build:
	$(compiler) $(flags) $(buildfile) -o $(compiledfile)

run: build
	./$(compiledfile)

# "clean" is not produced by make
.PHONY: clean

# delete built file
clean:
	rm -f $(compiledfile) $(outputFile)
