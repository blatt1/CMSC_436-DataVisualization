encounter.o: encounter.h encounter.cpp
	g++ -c encounter.cpp

default: encounter.o test.cpp
	g++ -std=c++11 encounter.o test.cpp -Wall -I/usr/include/cppconn -o test.o -L/usr/lib -lmysqlcppconn -lGL -lGLU -lglut

clean:
	rm ./*.o test
