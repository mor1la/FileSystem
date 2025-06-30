CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: fileHandlerTest.o

fileHandlerTest.o: main.o FileHandler.o
	$(CXX) $(CXXFLAGS) main.o FileHandler.o -o fileHandlerTest.o

main.o: main.cpp FileHandler.h FileExceptions.h
	$(CXX) $(CXXFLAGS) -c main.cpp

FileHandler.o: FileHandler.cpp FileHandler.h FileExceptions.h Consts.h
	$(CXX) $(CXXFLAGS) -c FileHandler.cpp

clean:
	rm -f *.o a.out
