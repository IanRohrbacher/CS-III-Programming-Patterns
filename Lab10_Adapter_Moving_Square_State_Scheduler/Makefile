compiler = g++

# compiler flags
flags = -std=c++17

# targets
adapter:
	$(compiler) $(flags) AdapterObject.cpp -o adapter
	./adapter
state:
	$(compiler) $(flags) State.cpp -o state
	./state

# "clean" and "bridge" are not produced by make
.PHONY: clean adapter state

# delete built file
clean:
	rm -f adapter state

