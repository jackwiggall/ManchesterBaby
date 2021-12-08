#include "Assembler.h"
using namespace std;



/**
 * @brief A function to tokenize a string based on a delimiter and return a corresponding vector
 * 
 * @param str The string to tokenize
 * @param delim The delimter string
 * @return vector<string> A vector of string tokens
 * 
 * @authors https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 * @note Comments added by group members
 */
vector<string> strsplit(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
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
    int instructionCounter = 0;
    int lineCounter = 0;
    string line;
    ifstream reader(filename);
    
    if (reader.is_open())
    {
        for (size_t i = 1; i <= 2; i++)
        {
            while (! reader.eof() )
            {
                
                
                
                try
                {
                    getline (reader,line);
                }
                catch(const std::exception& e)
                {
                    cout << "200" << endl; 
                }
              

                try
                {
                    processLine(line, instructionCounter, i);
                }
                catch(const std::exception& e)
                {
                    
                    int errorCode = stoi(e.what());
                    switch (errorCode)
                    {
                    case 100:
                        cout << errorCode << endl;
                        break;
                    case 101:
                        cout << errorCode << endl;
                        break;
                    case 102:
                        cout << errorCode << endl;
                        break;
                    case 103:
                        cout << errorCode << endl;
                        break;
                    case 104:
                        cout << errorCode << endl;
                        break;
                    
                    default:
                        cout << errorCode << endl;
                        break;
                    }

                    return;
                }
                

            }
            reader.clear();
            reader.seekg(0);
        }
        reader.close();
    }
    else{
        cout << "200" << endl;
    }
    

}

void Assembler::processLine(std::string line, int &counter, int iteration){
    if (counter >= maxMemory)
    {
        throw invalid_argument("104");
    }
    
    
    string splitLine = strsplit(line, ";").at(0);
    

    if (splitLine == "");
    {
        return;
    }
    
    
    vector<string> instruction = strsplit(splitLine, " ");

    if(instruction[0].find(':')){
        string label = instruction[0].substr(0,instruction[0].find(':'));
        if (sym.searchLabel(label) != -1)
        {
            throw invalid_argument("100");

        }
        
        sym.addLabel(label, binary::decimalToUnsignedBinary(counter, 12));

        string opcode = instruction[1];
        if (opcode == "VAR")
        {
            string operand = instruction[2];
            int op;
            try
            {
                op = stoi(operand);
            }
            catch(const std::exception& e)
            {
                throw invalid_argument("101");
            }
            
            out.addLine(binary::decimalToSignedBinary(op, 32), true);
        }
        
        int opcodedecimal = getOpcode(opcode);
        if (opcodedecimal == -1)
        {
            throw invalid_argument("102");
        }
        
        string opcodeBinary =binary::decimalToUnsignedBinary(opcodedecimal, 7);

        
        string operand = instruction[2];
        int index = sym.searchLabel(operand);
        if (index == -1)
        {
            if (iteration == 1)
            {
                out.addLine("", false);
            }
            else{
                throw invalid_argument("103");

            }
            
        }
        else{
            string address = sym.getAddress(index);
            string output = address + "0" + opcodeBinary + "000000000000";
            if (iteration == 1)
            {
                
                out.addLine(output, true);

            }
            else{
                out.setLine(output, true, counter);

            }
            
        }    
        
    }
    else{
         string opcode = instruction[0];
        if (opcode == "VAR")
        {
            string operand = instruction[1];
            int op;
            try
            {
                op = stoi(operand);
            }
            catch(const std::exception& e)
            {
                throw invalid_argument("101");
            }
            
            out.addLine(binary::decimalToSignedBinary(op, 32), true);
        }
        
        int opcodedecimal = getOpcode(opcode);
        if (opcodedecimal == -1)
        {
            throw invalid_argument("102");
        }
        
        string opcodeBinary =binary::decimalToUnsignedBinary(opcodedecimal, 7);

        
        string operand = instruction[1];
        int index = sym.searchLabel(operand);
        if (index == -1)
        {
            if (iteration == 1)
            {
                out.addLine("", false);
            }
            else{
                throw invalid_argument("103");

            }
            
        }
        else{
            string address = sym.getAddress(index);
            string output = address + "0" + opcodeBinary + "000000000000";
            if (iteration == 1)
            {
                
                out.addLine(output, true);

            }
            else{
                out.setLine(output, true, counter);

            }
            
        }    
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
