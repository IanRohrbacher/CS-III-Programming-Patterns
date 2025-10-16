compiler = g++

# compiler flags
flags = -std=c++17


test:
	$(compiler) $(flags) testHashmap.cpp -o testHashmap
	./testHashmap

run:
	$(compiler) $(flags) testHashmapUpdated.cpp -o testHashmapUpdated
	./testHashmapUpdated


# "clean" is not produced by make
.PHONY: clean

# delete built file
clean:
	rm -f testHashmap testHashmapUpdated

