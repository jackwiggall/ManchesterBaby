/**
 * @file main.cpp
 * @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
 * 
 * @brief This file is responsible for the main control flow of the Simulator program and displays the main menu
 */

#include "Simulator.h"
#include "Colors.h"
#include "helpers.h"
#include <iostream>

using namespace std;

/**
 * @brief Displays "Manchester Baby Simulator" using ASCII art
 */
void displayBigFont(){
    cout << endl;
    cout << "\x1B[34m█▀▄▀█ \x1B[36m▄▀█ \x1B[32m█▄ █ \x1B[33m█▀▀ \x1B[35m█ █ \x1B[31m█▀▀ \x1B[34m█▀ \x1B[36m▀█▀ \x1B[32m█▀▀ \x1B[33m█▀█   \x1B[35m█▄▄ \x1B[31m▄▀█ \x1B[34m█▄▄ \x1B[36m█▄█   \x1B[32m█▀ \x1B[33m█ \x1B[35m█▀▄▀█ \x1B[31m█ █ \x1B[34m█   \x1B[36m▄▀█ \x1B[32m▀█▀ \x1B[33m█▀█ \x1B[35m█▀█\x1B[0m" << endl;
    cout << "\x1B[34m█ ▀ █ \x1B[36m█▀█ \x1B[32m█ ▀█ \x1B[33m█▄▄ \x1B[35m█▀█ \x1B[31m██▄ \x1B[34m▄█ \x1B[36m █  \x1B[32m██▄ \x1B[33m█▀▄   \x1B[35m█▄█ \x1B[31m█▀█ \x1B[34m█▄█ \x1B[36m █    \x1B[32m▄█ \x1B[33m█ \x1B[35m█ ▀ █ \x1B[31m█▄█ \x1B[34m█▄▄ \x1B[36m█▀█ \x1B[32m █  \x1B[33m█▄█ \x1B[35m█▀▄\x1B[0m" << endl;
    cout << endl;
}

/**
 * @brief Outputs info text 
 */
void displayInfoMessage(){
    cout << endl;
    cout << "This program simulates the Manchester SSEM, nicknamed Manchester Baby. In order to use it, you will need a valid machine code file," << endl;
    cout << "which can be generated from valid Assembly code using the assembler program in \x1B[36m../assembler/\x1B[0m. " << endl;
    cout << endl;
    cout << "When you start the simulator, you will firstly need to set up the simulator. It will ask you for the path to your machine code file," << endl;
    cout << "and the memory size (the real Baby has 32 lines of memory, but you can expand it up to 4096 in this simulator)." << endl;
    cout << "Furthermore, you will be asked whether you want to turn on explanations (essentially verbose mode), to offer useful information " << endl;
    cout << "about what the Baby is currently doing. You can also toggle between step-by-step and continuous mode, which controls whether the" << endl;
    cout << "simulator halts after every instruction has been executed. The simulator will display the Baby's registers and store to your output." << endl;
    cout << endl;
}

/**
 * @brief Gets the user input 
 * 
 * @return int The users selection
 */
int getUserInput(){
    // Output prompt
    cout << "\x1B[36mStart Simulator [1]\t\x1B[31mExit[0]\x1B[0m" << endl;
    
    // Read in a string
    string input;
    cin >> input;

    // Clear the input buffer to remove any pending tokens
    cin.ignore(1000, '\n');

    // Evaluate response
    if(input == "1"){
        return 1;
    }
    else if(input == "0"){
        return 0;
    }
    return -1;
}

/**
 * @brief Starts the program and controls main loop
 * 
 * @return int Execution success code
 */
int main(){
    bool quit = false;
    do{
        helpers::clearScreen();
        displayBigFont();
        displayInfoMessage();
        int input = getUserInput();

        if(input == 1){
            Simulator s;
            try{
                s.setup();
                s.run();
            }
            catch(const exception &e){
                // Clear the screen
                helpers::clearScreen();

                // Print large font
                cout << BOLD(FRED("\n█▀█ █▀█ █▀█ █▀     █▀ █▀█ █▀▄▀█ █▀▀ ▀█▀ █ █ █ █▄ █ █▀▀   █ █ █ █▀▀ █▄ █ ▀█▀   █ █ █ █▀█ █▀█ █▄ █ █▀▀   ▀ ▄▀")) << endl;
                cout <<   BOLD(FRED("█▄█ █▄█ █▀▀ ▄█ █   ▄█ █▄█ █ ▀ █ ██▄  █  █▀█ █ █ ▀█ █▄█   ▀▄▀▄▀ ██▄ █ ▀█  █    ▀▄▀▄▀ █▀▄ █▄█ █ ▀█ █▄█   ▄ ▀▄\n")) << endl << endl;
                
                // Print error message
                cout << "The Simulator suffered a fatal error: " << endl;
                cout << e.what() << endl;

                // Press enter to continue
                helpers::waitForInput();
            }
        }
        else if(input == 0){
            quit = true;
        }
    }while(!quit);

    return 0;
}
