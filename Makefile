build_dir := ./build/

main: main.cpp $(wildcard *.hpp)
	g++ main.cpp -Wall -o $(build_dir)main -I./include/
