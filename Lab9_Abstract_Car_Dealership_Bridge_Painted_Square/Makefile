compiler = g++

# compiler flags
flags = -std=c++17

# targets
test:
	$(compiler) $(flags) CarTest.cpp CarFactory.cpp -o car
	./car
buyer:
	$(compiler) $(flags) CarBuyer.cpp CarFactory.cpp -o carTest
	./carTest

bridge:
	$(compiler) $(flags) bridgeFigures.cpp -o bridge
	./bridge


# "clean" and "bridge" are not produced by make
.PHONY: clean bridge

# delete built file
clean:
	rm -f car carTest bridge

