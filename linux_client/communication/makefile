chess=../chess/
main:main.o keyboard.o IKTCP_CLIENT.o package.o chess.o checkerboard.o global.o
	g++ -g -o main.out main.o keyboard.o IKTCP_CLIENT.o package.o
main.o:main.cpp keyboard.h IKTCP_CLIENT.h
	g++ -g -c -std=c++11 main.cpp
keyboard.o:keyboard.cpp
	g++ -g -c -std=c++11 keyboard.cpp
IKTCP_CLIENT.o:IKTCP_CLIENT.cpp
	g++ -g -c -std=c++11 IKTCP_CLIENT.cpp
package.o:package.cpp $(chess)chess.h $(chess)global.h $(chess)checkerboard.h
	g++ -g -c -std=c++11 package.cpp
chess.o:$(chess)chess.h
	g++ -g -c -std=c++11 $(chess)chess.cpp
checkerboard.o:$(chess)checkerboard.h
	g++ -g -c -std=c++11 $(chess)checkerboard.cpp
global.o:$(chess)global.h
	g++ -g -c -std=c++11 $(chess)global.cpp

clean:
	rm *.o
	rm main.out
