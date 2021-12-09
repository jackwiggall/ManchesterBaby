#include "Assembler.h"
#include <vector>
using namespace std;

/**
 * @brief Displays "Manchester Baby Simulator" using ASCII art
 */
void displayBigFont(){
    cout << endl;
    cout << "\x1B[34m█▀ \x1B[36m█▀ \x1B[32m█▀▀ \x1B[33m█▀▄▀█   \x1B[35m▄▀█ \x1B[31m█▀ \x1B[34m█▀ \x1B[36m█▀▀ \x1B[32m█▀▄▀█ \x1B[33m█▄▄ \x1B[35m█   \x1B[31m█▀▀ \x1B[34m█▀█" << endl;
    cout << "\x1B[34m▄█ \x1B[36m▄█ \x1B[32m██▄ \x1B[33m█ ▀ █   \x1B[35m█▀█ \x1B[31m▄█ \x1B[34m▄█ \x1B[36m██▄ \x1B[32m█ ▀ █ \x1B[33m█▄█ \x1B[35m█▄▄ \x1B[31m██▄ \x1B[34m█▀▄" << endl;
    cout << endl;
}

/**
 * @brief Get input from user
 * 
 * @param prompt Message to display
 * @return string The user input
 */
string getUserInput(string prompt){
    string input;
    cout << FMAG("[Assembler] ") << prompt << endl;
    getline(cin, input);

    return input;
}

/**
 * @brief Display a message to the user
 * 
 * @param prompt Message to display
 */
void printMessage(string message){
    cout << FMAG("[Setup] ") << message << endl;
    cout << endl;
}

void startAssembly(){
    string ifile = getUserInput("Please enter the path to your assembly language file:");
    cout << endl;
    string ofile = getUserInput("Please enter the filename for your machine code file:");
    cout << endl;
    string iSet = getUserInput("Please enter the path to your instruction set file, or press Enter to use the default:");
    if(iSet.empty()){
        iSet = "./instructions/default.txt";
        printMessage("Using default instruction set...");
    }
    else{
        cout << endl;
    }
    string memoryIn = getUserInput("Please enter the memory capacity for the Simulator that the program will be run on, or press Enter for 32 lines:");
    int memory = 32;
    if(!memoryIn.empty()){
        try {
            memory = stoi(memoryIn);
            if(memory < 32){
                memory = 32;
                printMessage("The memory size entered is too small. Setting memory to 32 lines...");
            }
        }
        catch(const std::exception& e) {
            printMessage("Your input was invalid. Setting memory to 32 lines...");
        }
    }
    else{
        printMessage("Setting memory size to 32 lines...");
    }

    Assembler a(memory);
    if(a.loadInstructionSet(iSet) && a.assemble(ifile)){
        a.exportToFile(ofile);
    }
}

int main() { 
    displayBigFont();
    startAssembly();
    return 1;
}