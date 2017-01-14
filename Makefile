all: client stdio play
	

client:
	g++ *.cpp main/client_main.cpp Fib2584/*.cpp -o ai_client -O3 -std=c++11

stdio:
	g++ *.cpp main/main.cpp Fib2584/*.cpp -o ai_stdio -O3 -std=c++11

play:
	g++ *.cpp main/play_main.cpp Fib2584/*.cpp -o play_game -O3 -std=c++11

clean:
	rm -f ai_client ai_stdio play_game TD_w.bin

