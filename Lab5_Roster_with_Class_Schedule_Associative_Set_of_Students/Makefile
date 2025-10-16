# txt file
txt = cs1.txt cs2.txt cs3.txt cs4.txt dropouts.txt

# output file
output = map.txt set.txt

# compiler
compiler = g++

# compiler flags
flags = -std=c++17


# delete built file
clean:
	rm -f resultMap resultSet $(output)


# not produced by make
.PHONY: buildMap buildSet runMap runSet testMap testSet


# build file
buildMap:
	$(compiler) $(flags) rosterMap.cpp -o resultMap

buildSet:
	$(compiler) $(flags) rosterSet.cpp -o resultSet


# run both tests saving their results to filess
runMap: buildMap
	./resultMap 0 $(txt) > map.txt
	diff map.txt classScheduleTestOutput.txt

runSet: buildSet
	./resultSet 0 $(txt) > set.txt
	diff set.txt studentEnrolledTestOutput.txt


# check if the programs output matches the desired output
testMap: buildMap
	./resultMap 1 map.txt > resultMap.txt

testSet: buildSet
	./resultSet 1 set.txt > resultSet.txt

