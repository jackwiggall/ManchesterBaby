/**
 * @file Assmbler.cpp
 * @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
 *
 * @brief The source code file for the Assembler class
 */

// Necessary includes
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
    do //loops for the length of the string getting split
    {
        pos = str.find(delim, prev); //gets the start of the string
        if (pos == string::npos) pos = str.length(); //checks length
        string token = str.substr(prev, pos-prev);  //shortens string
        if (!token.empty()) tokens.push_back(token); //if string not empty, push to back
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens; //returns string vector split
}

/**
 * @brief constucts a new assembler object
 * 
 * @param memory checks if memory is greater than or equal to 32
 */ 
Assembler::Assembler(int memory, bool verbose){
    this->verbose = verbose;
	  if(memory >= 32){ //check if enough memory exists or error
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

/**
 * @brief deconstucts assembler object
 */ 
Assembler::~Assembler(){
    // Empty deconstructor
}

/**
 * @brief loads the instuction set
 * 
 * @param filename name of file which the instruction set is being loaded from
 * @return if the file was read successfully
 */
bool Assembler::loadInstructionSet(std::string filename){
    // Declare local variables
    string line;
    int opcode;
    instruction instruction;
    
    // Load file
    ifstream reader(filename);
    
    // Return failed if file could not be read
    if (!reader) {
        cout << endl <<  FRED("[ERROR] ") << "Code 201: Instruction set file could not be read" << endl << endl;
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

/**
 * @brief gets the operation code
 * 
 * @param mneumonic used to specify the operation code
 * @return opcode or -1 if it is not found
 */ 
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

/**
 * @brief runs the assembler
 * 
 * @param filename the file which is to be read in
 * @returns if the function was successful
 */ 
bool Assembler::assemble(std::string filename){
    int instructionCounter = 0; //counter for the current instruction
    int lineCounter = 0; //counter for the current line
    string line; //the current line
    ifstream reader(filename);
    
	if (!reader) { //checks if it is read correctly
        cout << endl <<  FRED("[ERROR] ") << "Code 202: Assembly code file could not be read" << endl << endl;
        return false;
    }

    // Two assembly cycles
	for (int i = 1; i <= 2; i++)
	{
		while (getline(reader, line)) //while it is possible to get a line
		{
            lineCounter++;
            // Print verbose information
			if (verbose)
            {
                 cout << FMAG("[Assembling...] ") << "Processing line from " << filename << ": " << line << endl;
            }

			try
			{
                // Run line processing algorithm
				processLine(line, instructionCounter, i);
			}
            // Handle any errors
			catch(const std::invalid_argument& e)
			{
				int errorCode = stoi(e.what());
				switch (errorCode)
				{
				case 100:
					cout << endl <<  FRED("[ERROR] ") << "Code 100 at line " << lineCounter << ": Label is already defined elsewhere" << endl;
                    cout << line << endl << endl;
					break;
				case 101:
					cout << endl <<  FRED("[ERROR] ") << "Code 101 at line " << lineCounter << ": Value is not a signed 32-bit integer" << endl;
                    cout << line << endl << endl;
					break;
				case 102:
					cout << endl <<  FRED("[ERROR] ") << "Code 102 at line " << lineCounter << ": Instruction is not in instruction set" << endl;
                    cout << line << endl << endl;
					break;
				case 103:
					cout << endl <<  FRED("[ERROR] ") << "Code 103 at line " << lineCounter << ": Label does not exist" << endl;
                    cout << line << endl << endl;
					break;
				case 104:
					cout << endl <<  FRED("[ERROR] ") << "Code 104 at line " << lineCounter << ": Machine code exceeds memory size" << endl;
                    cout << line << endl << endl;
					break;
				
				default:
					cout << endl <<  FRED("[ERROR] ") << "Unknown assembly error occured at line " << lineCounter << endl;
                    cout << line << endl << endl;
					break;
				}

				return false;
			}
		}
        // Move back to start of file
		reader.clear();
		reader.seekg(0);
		instructionCounter = 0;
        lineCounter = 0;
	}
	reader.close();
    return true;
}

/**
 * @brief processes each line which is to be assembled
 * 
 * @param line that is being assembled
 * @param counter of which instuction it is processing
 * @param iteration of which line it is on
 */
void Assembler::processLine(std::string line, int &counter, int iteration){
    if (counter >= maxMemory) //checks if exceeding memory
    {
        throw invalid_argument("104");
    }
    string splitLine = line;

    if(line.find(';') != std::string::npos){ //removes ;
		splitLine = line.substr(0,line.find(';'));
	}

    if (splitLine == ""){ //checks if split is empty
        return;
    }

	if(out.getLineDone(counter) == true){ //checks if reached the end of the line
		counter++;
		return;
	}

    vector<string> instruction = strsplit(splitLine, " "); //splits line at spaces

    // Check for label
    if(instruction[0].find(':') != std::string::npos){
        string label = instruction[0].substr(0,instruction[0].find(':'));
        if(iteration == 1){
            // Validate and add label
			if (sym.searchLabel(label) != -1){
				throw invalid_argument("100");
			}
            string address = binary::decimalToUnsignedBinary(counter, 12);
			sym.addLabel(label, address);

            // Print verbose information
            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added label to symbol table: " << label << " : " << address << endl;
            }
		}

        string opcode = instruction[1];
		
        //if variable is read, set the 3rd part of the string to the operand
        if (opcode == "VAR")
        {
            string operand = instruction[2];

            // Validate operand
            int op;
            try
            {
                op = stoi(operand);
            }
            catch(const std::exception& e)
            {
                throw invalid_argument("101");
            }
            
            // Add to out buffer
            string value = binary::decimalToSignedBinary(op, 32);
            out.addLine(value, true);

            // Print verbose information
            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << value << endl;
            }
           
			counter++;
			return;
        }
        
        // Validates opcode
        int opcodedecimal = getOpcode(opcode);
        if (opcodedecimal == -1)
        {
            throw invalid_argument("102");
        }
        
        string opcodeBinary =binary::decimalToUnsignedBinary(opcodedecimal, 7);

		// Handle no operand case
        if(instruction.size() < 3){
            // Add to out buffer
            string output = "0000000000000" + opcodeBinary + "000000000000";
			out.addLine(output, true);

            // Display verbose information
            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
            }

			counter++;
			return;
		}

        //sets operand to the 3rd part of the split string 
        string operand = instruction[2];
        int index = sym.searchLabel(operand);
        if (index == -1)
        {
            if (iteration == 1)
            {
                // Add to out buffer
                out.addLine("", false);

                // Print verbose information
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
                // Add to out buffer
                out.addLine(output, true);

                // Print verbose information
                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
                }

				counter++;
				return;

            }
            else{
                // Add to out buffer
                out.setLine(output, true, counter);

                // Print verbose information
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

        // Check if instruction if VAR
        if (opcode == "VAR")
        {
            string operand = instruction[1];
            int op;
            // Validate value
            try
            {
                op = stoi(operand);
            }
            catch(const std::exception& e)
            {
                throw invalid_argument("101");
            }
            
            // Add to out buffer
            string value = binary::decimalToSignedBinary(op, 32);
            out.addLine(value, true);

            // Display verbose information
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
            // Add to out buffer
            string output = "0000000000000" + opcodeBinary + "000000000000";
			out.addLine(output, true);

            // Display verbose information
            if(verbose){
                cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
            }

			counter++;
			return;
		}

        string operand = instruction[1];

        // Look up label
        int index = sym.searchLabel(operand);
        if (index == -1)
        {
            if (iteration == 1)
            {
                // Add to out buffer
                out.addLine("", false);

                // Display verbose information
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
            if (iteration == 1)
            {
                // Add to out buffer
                out.addLine(output, true);

                // Display verbose information
                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Added line to output buffer and marked it as completed: " << output << endl;
                }

				counter++;
				return;
            }
            else{
                // Update out buffer
                out.setLine(output, true, counter);

                // Display verbose information
                if(verbose){
                    cout << FMAG("[Assembling...] ") << "Completed empty line "<< counter << " of the output buffer: " << output << endl;
                }

				counter++;
				return;
            }
        }    
    }
}

/**
 * @brief calls save to file if possible
 * 
 * @param filename the name of the file it is writing to
 */
void Assembler::exportToFile(string filename){
	// Saves to file or gives error
    try{
		out.saveToFile(filename);
        if (verbose)
        {
            cout << FMAG("[Assembling...] ") << "Writing output buffer to file " << filename << endl;
        }
	}
	catch(const exception &e){
		cout << endl <<  FRED("[ERROR] ") << "Code 203: File I/O error while saving output buffer to file" << endl << endl;
        return;
    }

     cout << endl << FMAG("[Assembling...] ") << "Assembly completed." << endl; 
}

/**
 * @brief Constucts a new symbol table object
 */
SymbolTable::SymbolTable(){
	//empty constructor
}

/**
 * @brief Destructs symbol table object
 */ 
SymbolTable::~SymbolTable(){
	//empty destructor
}

/**
 * @brief Adds a new label into the table
 * 
 * @param label The label to add
 * @param address The address the label represents
 */
void SymbolTable::addLabel(std::string label, std::string address){
	entry x;
	x.label = label;
	x.address = address;
	table.push_back(x);
}

/**
 * @brief Searches for a label in the symbol table and returns its index
 * 
 * @param label The label to search for
 * @return int the index of the label in the vector, or -1 if not found
 */
int SymbolTable::searchLabel(std::string label){
	//searches for the label or returns -1
    int i = 0;
	for (entry e : table) {
		if (e.label == label) {
			return i;
		}
		i++;
	}
	return -1;
}

/**
 * @brief Returns the address of the label at index
 * 
 * @param index The index to lookup
 * @return std::string The address
 */
string SymbolTable::getAddress(int index){
    //returns the address at the given index in the table
	return table.at(index).address;
}


/**
 * @brief Constucts a new output buffer
 */
OutputBuffer::OutputBuffer(){
    //empty constructor
}

/**
 * @brief Destructs output buffer object
 */ 
OutputBuffer::~OutputBuffer(){
    //empty deconstructor
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

/**
 * @brief saves the output to a textfile
 * 
 * @param filename the name of the output file
 */
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