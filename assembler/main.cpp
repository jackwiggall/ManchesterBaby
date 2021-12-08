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
    cout << FMAG("[Assembler] ") << prompt << endl;
    return "";
}

void startAssembly(){
    string ifile = getUserInput("Please enter the path to your ")
}

int main() { 
    displayBigFont();
    startAssembly();
    return 1;
}