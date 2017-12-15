main:ep.o utility.o
	g++ -o server ep.o utility.o
ep.o:ep.cpp utility.h
	g++ -g -c -std=c++11 ep.cpp
utility.o:
	g++ -g -c -std=c++11 utility.cpp
clean:
	rm *.o
	rm server