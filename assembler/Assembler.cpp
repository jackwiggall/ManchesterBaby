#include "Assembler.h"
using namespace std;

Assembler::Assembler(int memory){
	if(memory > 32){
		maxMemory = memory;
	}
	else{
		throw invalid_argument("001");
	}
}

Assembler::~Assembler(){

}

bool Assembler::loadInstructionSet(std::string filename){
    // Declare local variables
    string line;
    int opcode;
    instruction instruction;
    
    // Load file
    ifstream reader(filename);
    
    // Return failed if file could not be read
    if (!reader) {
        throw invalid_argument("201");
    }

    // Declare line counter
    int i = 0;
    // Loop through lines of file
    while(getline(reader, line)) {
		vector<string> token = strsplit(line,",");
        instruction.mneumonic = token[0]; //get mnemonic
        opcode = stoi(token[1]); //get opcode
        instruction.opcode = opcode; //convert opcode to int
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
