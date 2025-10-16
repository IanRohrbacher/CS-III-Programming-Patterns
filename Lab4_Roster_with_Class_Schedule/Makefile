# txt file
txt = cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

compiler = g++

# compiler flags
flags = -std=c++17

# build file
build:
	$(compiler) $(flags) roster.cpp -o result

buildObject:
	$(compiler) $(flags) rosterObject.cpp -o resultObject

# run both tests saving their results to files
run: build
	./result 0 $(txt) > result.txt
	diff result.txt classScheduleTestOutput.txt

runObject: buildObject
	./resultObject 0 $(txt) > resultObject.txt
	diff resultObject.txt classScheduleTestOutput.txt

# "clean" and "test" are not produced by make
.PHONY: clean test testObject

# delete built file
clean:
	rm -f result resultObject result.txt resultObject.txt

# check if the programs output matches the desired output
test: build
	./result 1 $(txt) > result.txt

testObject: buildObject
	./resultObject 1 $(txt) > resultObject.txt