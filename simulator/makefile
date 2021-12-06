#compiler
CC = g++

#flags
FLAGS = -std=c++17 -Wall -Wextra -pedantic -g

all: main.o Simulator.o binary.o helpers.o
	$(CC) $(FLAGS) main.o Simulator.o binary.o helpers.o -o outfile

main.o: main.cpp 
	$(CC) $(FLAGS) -c main.cpp

helpers.o: helpers.cpp helpers.h 
	$(CC) $(FLAGS) -c helpers.cpp

Simulator.o: Simulator.cpp Simulator.h Colors.h helpers.h
	$(CC) $(FLAGS) -c Simulator.cpp

binary.o: ../binary_library/binary.cpp ../binary_library/binary.h
	$(CC) $(FLAGS) -c ../binary_library/binary.cpp

clean:
	-@rm *.o outfile 2>/dev/null || true