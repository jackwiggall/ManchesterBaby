#include "Assembler.h"
#include <vector>

// ./assemble source destination isntructionset memory 
int main() { 
    Assembler a(32);
    a.loadInstructionSet("./SSEM-Instructions.txt");
    a.assemble("./programs/test.txt");
    a.exportToFile("assemlbed.txt");
}