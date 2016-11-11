all:
	g++ -std=c++11 -Wall -O3 *.cpp -o play_game

clean:
	rm play_game

run:
	./play_game < input.txt
