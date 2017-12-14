main:chess.o checkerboard.o global.o main.o
	g++ -o main.out chess.o checkerboard.o global.o main.o
main.o:
	g++ -g -c -std=c++11 main.cpp
chess.o:chess.h
	g++ -g -c -std=c++11 chess.cpp
checkerboard.o:checkerboard.h
	g++ -g -c -std=c++11 checkerboard.cpp
global.o:global.h
	g++ -g -c -std=c++11 global.cpp
clean:
	rm *.o 
	rm main.out
