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
	//empty constructor
}

SymbolTable::~SymbolTable(){
	//empty destructor
}

void SymbolTable::addLabel(std::string label, std::string address){
	
	entry x;
	x.label = label;
	x.address = address;
	table.push_back(x);

}

int SymbolTable::searchLabel(std::string label){

	for (int i=0;i<table.size()-1;i++) {
		if (table.at(i).label==label) {
			return i;
		}
	}
	return -1;
}

string SymbolTable::getAddress(int index){

	return table.at(index).address;
}



OutputBuffer::OutputBuffer(){

}

OutputBuffer::~OutputBuffer(){

}

/**
 * @brief Checks if line with certain lineNumber has completed output
 * 
 * @param lineNumber, checks if the output of this line is complete
 * @return boolean, true for done and false otherwise
 */

bool OutputBuffer::getLineDone(int lineNumber){
    //if line with this lineNumber is done
    if (buffer.at(lineNumber).done) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Adds a new line to the outputBuffer
 * 
 * @param output the binary value
 * @param done whether the line is complete
 * @return std::string The address
 */
void OutputBuffer::addLine(std::string output, bool done){
    entry x;

    //add to entry
    x.output = output;
	x.done = done;

	buffer.push_back(x);
}

/**
 * @brief sets line that was not done after first cycle
 * 
 * @param output the binary value
 * @param done whether the line is complete
 * @param lineNumber the line which was not complete
 */  
void OutputBuffer::setLine(std::string output, bool done, int lineNumber){
    //if line is not done set values
    if (getLineDone(lineNumber) == false) {
        buffer.at(lineNumber).output = output;
        buffer.at(lineNumber).done = done;
    }
}
