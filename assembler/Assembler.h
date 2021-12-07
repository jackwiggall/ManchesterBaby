#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <fstream>
#include "../binary_library/binary.h"

class Assembler{
    struct instruction{
        std::string mneumonic;
        int opcode;
    };
    private:
        int currentLine = 0;
        int maxMemory = 32;

        SymbolTable sym;
        OutputBuffer out;

        std::vector<instruction> instructionSet;

    public:
        Assembler();
        ~Assembler();

        bool loadInstructionSet(std::string filename);
        int getOpcode(std::string mneumonic);

        void assemble(std::string filename);
        void processLine(std::string line);
};

class SymbolTable{
    struct entry {
        std::string label;
        std::string address;
    };

    private:
        std::vector<entry> table;

    public:
        SymbolTable();
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
        std::string output;
        bool done;
    };

    private:
        std::vector<entry> buffer;

    public:
        OutputBuffer();
        ~OutputBuffer();

        std::vector<entry> getBuffer(){return buffer;};
        bool getLineDone(int lineNumber);
        void addLine(std::string output, bool done);
        void setLine(std::string output, bool done, int lineNumber);
};

#endif