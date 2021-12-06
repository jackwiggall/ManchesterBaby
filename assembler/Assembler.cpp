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
