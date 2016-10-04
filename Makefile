all:
	g++ -std=c++11 -O3 Fib2584/*.cpp *.cpp -o play_game

clean:
	rm play_game

run:
	./play_game 1000
