main:main.o keyboard.o IKTCP_CLIENT.o
	g++ -g -o main.out main.o keyboard.o IKTCP_CLIENT.o
main.o:main.cpp keyboard.h IKTCP_CLIENT.h
	g++ -g -c -std=c++11 main.cpp
keyboard.o:keyboard.cpp
	g++ -g -c -std=c++11 keyboard.cpp
IKTCP_CLIENT.o:IKTCP_CLIENT.cpp
	g++ -g -c -std=c++11 IKTCP_CLIENT.cpp
# main:main.cpp
# 	g++ -g -std=c++11 -o  main.out main.cpp
clean:
	rm *.o
	rm main.out
