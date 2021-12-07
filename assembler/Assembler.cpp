#include "Assembler.h"
using namespace std;

Assembler::Assembler(){

}

Assembler::~Assembler(){

}

void Assembler::loadInstructionSet(std::string filename){

}

int Assembler::getOpcode(std::string mneumonic){

}

void Assembler::assemble(std::string filename){

}

void Assembler::processLine(std::string line){

}



SymbolTable::SymbolTable(){
	//empty constructor
}

SymbolTable::~SymbolTable(){
	delete [] table; //delete dis
}

void SymbolTable::addLabel(std::string label, std::string address){
	
	entry x;
	x.label = label;
	x.address = address;
	table.push(x);

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



bool OutputBuffer::getLineDone(int lineNumber){

}

void OutputBuffer::addLine(std::string output, bool done){

}

void OutputBuffer::setLine(std::string output, bool done, int lineNumber){

}
