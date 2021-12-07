#include "Assembler.h"
using namespace std;

Assembler::Assembler(){

}

Assembler::~Assembler(){

}

bool Assembler::loadInstructionSet(std::string filename){
    // Declare local variables
    string line;
    char opcode;
    instruction instruction;
    
    // Load file
    ifstream reader(filename);
    
    // Return failed if file could not be read
    if (!reader) {
        //error = "The file does not exist or could not be opened. Verify the filename is valid and that the file is not currenly used by any other program.";
        return false;
    }

    // Declare line counter
    int i = 0;
    // Loop through lines of file
    while(getline(reader, line)) {
        instruction.mneumonic = line.substr(0,2); //get mnemonic
        opcode = line.back(); //get opcode
        instruction.opcode = (int)opcode - 48; //convert opcode to int
        instructionSet.push_back(instruction); //add to set
    }
    return true;
}

int Assembler::getOpcode(std::string mneumonic){
    //loop through set
    for (size_t i = 0; i < instructionSet.size(); i++) {
        //if matches return opcode
        if(instructionSet.at(i).mneumonic == mneumonic) {
            return instructionSet.at(i).opcode;
        }
    }
    //if not found return -1
    return -1;
}

void Assembler::assemble(std::string filename){

}

void Assembler::processLine(std::string line){

}



SymbolTable::SymbolTable(){

}

SymbolTable::~SymbolTable(){

}

void SymbolTable::addLabel(std::string label, std::string address){

}

int SymbolTable::searchLabel(std::string label){

}

string SymbolTable::getAddress(int index){

}



OutputBuffer::OutputBuffer(){

}

OutputBuffer::~OutputBuffer(){

}



bool OutputBuffer::getLineDone(int lineNumber){

}

void OutputBuffer::addLine(std::string output, bool done){

}

void OutputBuffer::setLine(std::string output, bool done, int lineNumber){

}
