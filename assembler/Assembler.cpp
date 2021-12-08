#include "Assembler.h"
using namespace std;



/**
 * @brief A function to tokenize a string based on a delimiter and return a corresponding vector
 * 
 * @param str The string to tokenize
 * @param c The delimter character
 * @return vector<string> A vector of string tokens
 * 
 * @authors https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
 * @note Comments added by group members
 */
vector<string> strsplit(const char *str, char c){
    // A vector to hold the tokens
    vector<string> result;

    // Iterate over string and push-back when delimiter found
    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    // Return the results
    return result;
}

Assembler::Assembler(){

}

Assembler::~Assembler(){

}

void Assembler::loadInstructionSet(std::string filename){

}

int Assembler::getOpcode(std::string mneumonic){

}

void Assembler::assemble(std::string filename){
    string line;
    ifstream reader(filename);
    int counter =0;
    if (reader.is_open())
    {
        while (! reader.eof() )
        {
            
            getline (reader,line);
            processLine(line, counter);

    
        }
    reader.close();
    }

    

}

void Assembler::processLine(std::string line, int &counter){
    string splitLine = strsplit(line.c_str(), ';').at(0);
    

    if (splitLine == "");
    {
        return;
    }
    
    
    vector<string> instruction = strsplit(splitLine.c_str(), ' ');

    if(instruction[0].find(':')){
        string label = instruction[0].substr(0,instruction[0].find(':'));
        sym.addLabel(label, binary::decimalToUnsignedBinary(counter, 12));

        string opcode = instruction[1];
        int opcodedecimal = getOpcode(opcode);
    }
    else{

    }


    
    counter++;
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
