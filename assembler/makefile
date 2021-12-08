# @file makefile
# @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
# 
# @brief This makefile automates the compilation process of the Assembler program

##################################################################################################################
# To compile the Simulator fully, simply run "make" while in the Assembler directory                             #
##################################################################################################################

# Define compiler
CC = g++

# Define compiler flags
FLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# This target compiles the entire program
all: main.o Assembler.o binary.o
	$(CC) $(FLAGS) main.o Assembler.o binary.o -o assemble.out

exec: all
	-@rm *.o 2>/dev/null || true

# main.o target compiles the main source code into object code
main.o: main.cpp 
	$(CC) $(FLAGS) -c main.cpp

# helpers.o target compiles the helpers source code into object code
Assembler.o: Assembler.cpp Assembler.h 
	$(CC) $(FLAGS) -c Assembler.cpp

# binary.o target compiles the binary library into object code
binary.o: ../binary_library/binary.cpp ../binary_library/binary.h
	$(CC) $(FLAGS) -c ../binary_library/binary.cpp

# This target clears every outfiles and object code files
clean:
	-@rm *.o assemble.out 2>/dev/null || true