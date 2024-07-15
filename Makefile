CC := g++

build_dir := ./build/
src_files := $(wildcard ./src/*.cpp)
header_files := $(wildcard ./include/*.hpp)

flags := -Wall

main: main.cpp $(src_files) $(header_files)
	$(CC) main.cpp $(src_files) $(flags) -o $(build_dir)main -I./include/
