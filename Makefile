all:
	g++ -std=c++11 -O3 Fib2584/*.cpp *.cpp -o play_game

clean:
	rm play_game TD_w.bin

run:
	./play_game 100000
