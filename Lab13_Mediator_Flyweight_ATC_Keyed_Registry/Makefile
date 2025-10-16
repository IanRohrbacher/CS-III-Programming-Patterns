# compiler flags
compiler = g++
flags = -std=c++17

# targets
ATC:
	$(compiler) $(flags) ATC.cpp -o ATC
	./ATC

registry:
	$(compiler) $(flags) registry.cpp -o registry
	./registry

# "clean" is not produced by make
.PHONY: clean ATC registry

# delete built file
clean:
	rm -f ATC registry
