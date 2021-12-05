#compiler
CC = g++

#flags
FLAGS = -std=c++17 -Wall -Wextra -pedantic -g

all: Simulator.o binary.o
	$(CC) $(FLAGS) Simulator.o binary.o -o outfile

Simulator.o: Simulator.cpp Simulator.h Colors.h
	$(CC) $(FLAGS) -c Simulator.cpp

binary.o: ../binary_library/binary.cpp ../binary_library/binary.h
	$(CC) $(FLAGS) -c ../binary_library/binary.cpp

clean:
	-@rm *.o outfile 2>/dev/null || true