# compiler flags
compiler = g++
flags = -std=c++17

# targets
genealogy:
	$(compiler) $(flags) genealogy.cpp -o genealogy
	./genealogy

history:
	$(compiler) $(flags) history.cpp -o history
	./history

# "clean" is not produced by make
.PHONY: clean genealogy history

# delete built file
clean:
	rm -f genealogy history
