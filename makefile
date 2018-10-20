all: cpp_ci

cpp_ci: cpp_ci.o
	g++ cpp_ci.o -o cpp_ci

cpp_ci.o: src/cpp_ci.cpp
	g++ -c src/cpp_ci.cpp