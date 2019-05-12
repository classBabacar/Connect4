build: game

game: main.cc connect4.cc colors.h
	g++ -o game *.cc

clean:
	rm game