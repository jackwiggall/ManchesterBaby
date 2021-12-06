/**
 * @file helpers.cpp
 * @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
 *
 * @brief Source code file implementing some helper functions used across the Simulator program
 */

// Necessary includes
#include <iostream>
using namespace std;

namespace helpers {
    /**
     * @brief Function to clear the screen on POSIX/UNIX systems 
     */
    void clearScreen(){
        cout << "\033[2J\033[1;1H";
    }

    /**
     * @brief Function to prompt the user to hit Enter to continue 
     */
    void waitForInput(){
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}