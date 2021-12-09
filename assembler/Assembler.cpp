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

Assembler::Assembler(int memory, bool verbose){
    this->verbose = verbose;

	if(memory >= 32){
		maxMemory = memory;
        if (verbose)
        {
            cout << FMAG("[Assembling...] ") << "Memory size set to " << memory <<endl;
        }
        
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
    if (verbose)
    {
        cout << FMAG("[Assembling...] ") << "Instruction set loaded from file " << filename << endl;
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
			if (verbose)
            {
                 cout << FMAG("[Assembling...] ") << "Processing line from " << filename << ": " << line << endl;
            }

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
            string address = binary::decimalToUnsignedBinary(counter, 12);
			sym.addLabel(label, address);
            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added label to symbol table: " << label << " : " << address << endl;
            }
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
            
            string value = binary::decimalToSignedBinary(op, 32);
            out.addLine(value, true);
            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << value << endl;
            }
           
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

            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
            }

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

                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Added empty line to output buffer and marked it as incomplete. " << endl;
                }

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

                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
                }

				counter++;
				return;

            }
            else{
                out.setLine(output, true, counter);

                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Completed empty line "<< counter << " of the output buffer: " << output << endl;
                }

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
            
            string value = binary::decimalToSignedBinary(op, 32);
            out.addLine(value, true);

            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << value << endl;
            }

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

            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
            }

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

                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Added empty line to output buffer and marked it as incomplete." << endl;
                }

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
            // if (verbose)
            // {
            //     cout << FMAG("[Assembling...] ") << "Encoded in machine code: " <<output << endl;
            // }
            if (iteration == 1)
            {
                out.addLine(output, true);

                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
                }

				counter++;
				return;
            }
            else{
                out.setLine(output, true, counter);

                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Completed empty line "<< counter << " of the output buffer: " << output << endl;
                }

				counter++;
				return;
            }
            
        }    
    }
}

void Assembler::exportToFile(string filename){
	try{
		out.saveToFile(filename);
        if (verbose)
        {
            cout << FMAG("[Assembling...] ") << "Writing output buffer to file " << filename << endl;
        }
	}
	catch(const exception &e){
		cout << "203" << endl;
	}

     cout << endl << FMAG("[Assembling...] ") << "Assembly completed." << endl; 
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