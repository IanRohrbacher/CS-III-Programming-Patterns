# file to build
log = log.cpp
game = templateMethodGames.cpp

# log txt
logTxt = log.txt

# compiled
compiledLog = log
compiledGame = game

# compiler flags
compiler = g++
flags = -std=c++17

# targets
log: $(log)
	$(compiler) $(flags) $(log) -o $(compiledLog)

log_run: log
	./$(compiledLog) $(logTxt)

game: $(game)
	$(compiler) $(flags) $(game) -o $(compiledGame) && ./$(compiledGame) 0

rps: $(game)
	$(compiler) $(flags) $(game) -o $(compiledGame) && ./$(compiledGame) 1

# "clean" is not produced by make
.PHONY: clean

# delete built file
clean:
	rm -f $(compiledLog) $(compiledGame) $(logTxt)
