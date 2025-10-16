# file to build
lemon = lemons.cpp
orange = oranges.cpp
apple = apples.cpp
peach = peaches.cpp

# file to output
targetLemon = lemons.out
targetOrange = oranges.out
targetApple = apples.out
targetPeach = peaches.out

compiler = g++

# compiler flags
flags = -std=c++17

# default target
all: lemon orange apple peach

lemon:
	$(compiler) $(flags) $(lemon) -o $(targetLemon)
	./$(targetLemon)

orange:
	$(compiler) $(flags) $(orange) -o $(targetOrange)
	./$(targetOrange)

apple:
	$(compiler) $(flags) $(apple) -o $(targetApple)
	./$(targetApple)

peach:
	$(compiler) $(flags) $(peach) -o $(targetPeach)
	./$(targetPeach)

# "clean" is not produced by make
.PHONY: clean

# delete built file
clean:
	rm -f $(targetLemon) $(targetOrange) $(targetApple) $(targetPeach)

