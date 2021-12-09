# Welcome to the Manchester Baby Project 👋

The Manchester Baby project consists of a Simulator of the Manchester SSEM (also known as the Manchester Baby), as well as an assembler for SSEM Assembly code. Both parts have been modified to work with larger memory stores, which can be increased to up to 4096 memory locations. Furthermore, the addition of immediate addressing is planned.

## Authors
👤 **Jack Wiggall, Heather Currie, Ross Coombs, Elliot Scott, Kai Uerlichs**

## Table of Contents
- Simulator guide
- Assembler guide
- Extended instruction set
----
## Important
The Simulator provided uses an extended instruction set. For more information, go to [Extended instruction set](#extended-instruction-set).

----
## Simulator
The Simulator program is located in the folder `./simulator`. It is written in **C++** and is intended to be compiled using **gcc**.

### Building the Simulator
To build the Simulator, you can use the included **makefile**. The makefile expects the **gcc** compiler by default. If you want to change the compiler, or want to edit the compilation flags, simply edit the corresponding variable in the makefile. 

Finally, to compile the simulator and produce an executable, run:
```
make exec
```
To additionally retain the build files (.o files), run:
```
make
```

### Using the Simulator
When you run the executable, you will be greeted with the main menu and a short info text about using the Simulator. 

Press [1] and follow the instructions on screen to select the program to run (examples provided in `./programs`), the display settings, and the memory size (32 to 4096). Once completed, the Simulator instance will be launched.

While the Simulator is running, you can view the fetch-execute cycle if explanations are enabled, and you will be shown the current register and store states at various points in the program execution. After the program is terminated, you will see the display again, before being given the option to store it in `./output`.

Back in the main menu, you can either start another Simulator, or exit by pressing [0].

## Assembler
The Assembler program is written to complement the Simulator. It is located in `./assembler`, written in **C++**.

### Building the Assembler
To build the Assembler, you can use the included **makefile**. The makefile expects the **gcc** compiler by default. If you want to change the compiler, or want to edit the compilation flags, simply edit the corresponding variable in the makefile. 

Finally, to compile the Assembler and produce an executable, run:
```
make exec
```
To additionally retain the build files (.o files), run:
```
make
```

### Using the Assembler
When you run the executable, the program will ask you for the following:

1. Assembly code file path
2. File name for the output file
3. Instruction set file path (or use default)
4. Memory size (or use default)

Note that [3] specifies a file similar to those in `./instructions`. These files tell the Assembler which mneumonic opcodes are valid, and allow the user to quickly add or change instructions set for their specific needs and extensions.

Note that [4] specifies the memory size. This parameter is used to verify that a given Assembly program can be store in a SSEM store of the specified size. If the program exceeds the memory size, an error will be thrown.

After filling in the required information, you have the option to activate verbose mode for assembly information, and the assemble process will commence, writing a machine code file to `./output`.

**Error Codes**

    100    Label is already defined elsewhere
    101    Value is not a signed 32-bit integer
    102    Operand not in instruction set
    103    Label does not exist
    104    Machine code exceeds memory size

    200    Undefined I/O error
    201    Instruction set could not be read
    202    Assembly code file could not be read
    203    File I/O error while saving machine code to file

## Extended Instruction set
The Simulator runs on an extended instruction set. **Any programs written for the original instruction set will work as before** under the new instruction set, and the opcode numbers remain the same.

To accomodate a larger instruction set, bits 13-19 of any instruction in machine code will be used to allow for up to 128 instructions. However, the extended instruction set only holds 14 instructions.

| MNEUMONIC | DECIMAL | BINARY | Description |
| ---- | ---- | ---- | ---- |
| JMP | 0 | 0000000 | CI = S |
| JRP | 1 | 1000000 | CI = CI + S |
| LDN | 2 | 0100000 | A = -S |
| STO | 3 | 1100000 | S = A |
| SUB | 4 | 0010000 | A = A - S |
| SUB | 5 | 1010000 | A = A - S |
| CMP | 6 | 0110000 | CI + 1 if A is negative |
| STP | 7 | 1110000 | Stop the program |
| ADD | 8 | 0001000 | A = A + S |
| MTP | 9 | 1001000 | A = A * S |
| MIN | 10 | 0101000 | A = MIN(A,S) |
| MAX | 11 | 1101000 | A = MAX(A,S) |
| LDP | 12 | 0011000 | A = S |
| INC | 13 | 1011000 | A = A + 1 |

To assemble an assembly language program with the extended instruction set, make sure to enter the extended instruction set file when prompted (`./instructions/extended.txt`).