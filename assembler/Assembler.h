#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../binary_library/binary.h"
#include "Colors.h"

class SymbolTable{
    struct entry {
        /**
         * @brief string label holds the labels stored in the symbol table
         */ 
        std::string label;

        /**
         * @brief string address holds the addresses stored in the symbol table
         */ 
        std::string address;
    };

    private:
        /**
         * @brief This entry vector reprsents the symbol table
         */
        std::vector<entry> table;

    public:
        /**
         * @brief Constucts a new symbol table object
         */
        SymbolTable();

        /**
         * @brief Destructs symbol table object
         */ 
        ~SymbolTable();

        /**
         * @brief Adds a new label into the table
         * 
         * @param label The label to add
         * @param address The address the label represents
         */
        void addLabel(std::string label, std::string address);

        /**
         * @brief Searches for a label in the symbol table and returns its index
         * 
         * @param label The label to search for
         * @return int the index of the label in the vector, or -1 if not found
         */
        int searchLabel(std::string label);

        /**
         * @brief Returns the address of the label at index
         * 
         * @param index The index to lookup
         * @return std::string The address
         */
        std::string getAddress(int index);

};

class OutputBuffer{
    struct entry {
        /**
         * @brief string output holds the output in the output buffer
         */  
        std::string output;

        /**
         * @brief boolean done stores if the entry in the output buffer is complete
         */  
        bool done;
    };

    private:
        /**
         * @brief This entry vector reprsents the output buffer
         */  
        std::vector<entry> buffer;

    public:
        /**
         * @brief Constucts a new output buffer
         */
        OutputBuffer();

        /**
         * @brief Destructs output buffer object
         */ 
        ~OutputBuffer();

        /**
         * @brief get and return the buffer
         * @return entry vector, which represents the output buffer
         */
        std::vector<entry> getBuffer(){return buffer;};

        /**
         * @brief Checks if line with certain lineNumber has completed output
         * 
         * @param lineNumber, checks if the output of this line is complete
         * @return boolean, true for done and false otherwise
         */
        bool getLineDone(int lineNumber);

        /**
         * @brief Adds a new line to the outputBuffer
         * 
         * @param output the binary value
         * @param done whether the line is complete
         * @return std::string The address
         */
        void addLine(std::string output, bool done);

        /**
         * @brief sets line that was not done after first cycle
         * 
         * @param output the binary value
         * @param done whether the line is complete
         * @param lineNumber the line which was not complete
         */  
        void setLine(std::string output, bool done, int lineNumber);

        /**
         * @brief saves the output to a textfile
         * 
         * @param filename the name of the output file
         */
        void saveToFile(std::string filename);
};

class Assembler{
    struct instruction{
        /**
         * @brief string mneumonic used to specify the opcode
         */
        std::string mneumonic;

        /**
         * @brief int opcode holds the operation codes value
         */
        int opcode;
    };
    private:
        /**
         * @brief int currentLine is which line the assembler is processing
         */
        int currentLine = 0;

        /**
         * @brief int maxMemory is the max amount of memory that can be used
         */
        int maxMemory = 32;

        /**
         * @brief SymbolTable object created named sym
         */
        SymbolTable sym;

        /**
         * @brief outputBuffer object created named out
         */
        OutputBuffer out;

        /**
         * @brief vector of instructions created named instructionSet
         */
        std::vector<instruction> instructionSet;

    public:
        /**
         * @brief constucts a new assembler object
         * 
         * @param memory checks if memory is greater than or equal to 32
         */ 
        Assembler(int memory);

        /**
         * @brief deconstucts assembler object
         */ 
        ~Assembler();

        /**
         * @brief loads the instuction set
         * 
         * @param filename name of file which the instruction set is being loaded from
         * @return if the file was read successfully
         */
        bool loadInstructionSet(std::string filename);

        /**
         * @brief gets the operation code
         * 
         * @param mneumonic used to specify the operation code
         * @return opcode or -1 if it is not found
         */ 
        int getOpcode(std::string mneumonic);

        /**
         * @brief runs the assembler
         * 
         * @param filename the file which is to be read in
         * @returns if the function was successful
         */ 
        bool assemble(std::string filename);

        /**
         * @brief processes each line which is to be assembled
         * 
         * @param line that is being assembled
         * @param counter of which instuction it is processing
         * @param iteration of which line it is on
         */
        void processLine(std::string line, int &counter, int iteration);

        /**
         * @brief calls save to file if possible
         * 
         * @param filename the name of the file it is writing to
         */
        void exportToFile(std::string filename);
      
      
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
        std::vector<std::string> strsplit(const std::string& str, const std::string& delim);
};

#endif