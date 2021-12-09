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
vector<string> Assembler::strsplit(const string& str, const string& delim)
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

Assembler::Assembler(int memory){
	if(memory >= 32){
		maxMemory = memory;
	}
	else{
		cout << "204" << endl;
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
        cout << "201" << endl;
        return false;
    }

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

bool Assembler::assemble(std::string filename){
    int instructionCounter = 0;
    int lineCounter = 0;
    string line;
    ifstream reader(filename);
    
	if (!reader) {
        throw invalid_argument("202");
    }

	for (int i = 1; i <= 2; i++)
	{
		while (getline(reader, line))
		{
			try
			{
				processLine(line, instructionCounter, i);
				
			}
			catch(const std::invalid_argument& e)
			{
				int errorCode = stoi(e.what());
				switch (errorCode)
				{
				case 100:
					cout << FRED("Error ") << errorCode << FRED(" on line ") << lineCounter << FRED(". Label is already defined elsewhere.") << endl;
					break;
				case 101:
					cout << FRED("Error ") << errorCode << FRED(" on line ") << lineCounter << FRED(". Value is not a signed 32-bit integer.") << endl;
					break;
				case 102:
					cout << FRED("Error ") << errorCode << FRED(" on line ") << lineCounter << FRED(". Operand not in instruction set.") << endl;
					break;
				case 103:
					cout << FRED("Error ") << errorCode << FRED(" on line ") << lineCounter << FRED(". Label does not exist.") << endl;
					break;
				case 104:
					cout << FRED("Error ") << errorCode << FRED(" on line ") << lineCounter << FRED(". Machine code exceeds memory size.") << endl;
					break;
				
				default:
					cout << FRED("Error ") << errorCode << FRED(" on line ") << lineCounter << FRED(". Unknown Error.") << endl;
					break;
				}

				return false;
			}
			

		}
		reader.clear();
		reader.seekg(0);
		instructionCounter = 0;
	}
	reader.close();
    return true;
}

void Assembler::processLine(std::string line, int &counter, int iteration){
    if (counter >= maxMemory)
    {
        throw invalid_argument("104");
    }
    string splitLine = line;

    if(line.find(';') != std::string::npos){
		splitLine = line.substr(0,line.find(';'));
	}

    if (splitLine == ""){
        return;
    }

	if(out.getLineDone(counter) == true){
		counter++;
		return;
	}

    vector<string> instruction = strsplit(splitLine, " ");

    if(instruction[0].find(':') != std::string::npos){
        string label = instruction[0].substr(0,instruction[0].find(':'));
        if(iteration == 1){
			if (sym.searchLabel(label) != -1){
				throw invalid_argument("100");
			}
			sym.addLabel(label, binary::decimalToUnsignedBinary(counter, 12));
		}

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
			counter++;
			return;
        }
        
        int opcodedecimal = getOpcode(opcode);
        if (opcodedecimal == -1)
        {
            throw invalid_argument("102");
        }
        
        string opcodeBinary =binary::decimalToUnsignedBinary(opcodedecimal, 7);

		// Handle no operand case
        if(instruction.size() < 3){
            string output = "0000000000000" + opcodeBinary + "000000000000";
			out.addLine(output, true);
			counter++;
			return;
		}

        string operand = instruction[2];
        int index = sym.searchLabel(operand);
        if (index == -1)
        {
            if (iteration == 1)
            {
                out.addLine("", false);
				counter++;
				return;
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
				counter++;
				return;

            }
            else{
                out.setLine(output, true, counter);
				counter++;
				return;

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
			counter++;
			return;
        }
        
        int opcodedecimal = getOpcode(opcode);
        if (opcodedecimal == -1)
        {
            throw invalid_argument("102");
        }
        
        string opcodeBinary =binary::decimalToUnsignedBinary(opcodedecimal, 7);

		// Handle no operand case
        if(instruction.size() < 2){
            string output = "0000000000000" + opcodeBinary + "000000000000";
			out.addLine(output, true);
			counter++;
			return;
		}

        string operand = instruction[1];
        int index = sym.searchLabel(operand);
        if (index == -1)
        {
            if (iteration == 1)
            {
                out.addLine("", false);
				counter++;
				return;
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
				counter++;
				return;
            }
            else{
                out.setLine(output, true, counter);
				counter++;
				return;
            }
            
        }    
    }
}

void Assembler::exportToFile(string filename){
	try{
		out.saveToFile(filename);
	}
	catch(const exception &e){
		cout << "203" << endl;
	}
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
	int i = 0;
	for (entry e : table) {
		if (e.label == label) {
			return i;
		}
		i++;
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
    if(lineNumber >= (int) buffer.size()){
		return false;
	}
    if (buffer.at(lineNumber).done) {
        return true;
    } 
	else {
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

void OutputBuffer::saveToFile(string filename){
    ofstream out;
    out.open("./output/"+filename);

    // Throw exception if file creation was not possible
    if(!out){
        throw runtime_error("203");
    }

    for(entry e : buffer){
        out << e.output << endl;
    }

    // Close output stream
    out.close();

    return;
}