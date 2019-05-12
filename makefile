build: Game

Game: main.o connect4.o 
	g++ -c -WALL main.o connect4.o -o Game

main.o: colors.h connect.4 main.cc
	g++ -c -WALL main.cc

connect4.o: color.h connect4.h connect4.cc
	g++ -c -WALL connect4.cc
