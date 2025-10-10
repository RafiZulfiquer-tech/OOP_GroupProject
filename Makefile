CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

all: test_environment

test_environment: Environment.o Entity.o test_environment.o
	$(CXX) $(CXXFLAGS) -o test_environment Environment.o Entity.o test_environment.o

Environment.o: Environment.cpp Environment.h
	$(CXX) $(CXXFLAGS) -c Environment.cpp

Entity.o: Entity.h
	$(CXX) $(CXXFLAGS) -c -o Entity.o Entity.cpp

test_environment.o: test_environment.cpp Environment.h Entity.h
	$(CXX) $(CXXFLAGS) -c test_environment.cpp

clean:
	rm -f *.o test_environment
