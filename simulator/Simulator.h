/**
 * @file Simulator.h
 * @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
 *
 * @brief The header file for the Simulator class, representing a functionally expanded model of the Manchester SSEM (Baby)
 */

// Header guard
#ifndef SIMULATOR_H
#define SIMULATOR_H

// Necessary includes
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
#include "../binary_library/binary.h"
using namespace std;

class Simulator {
    private:
        /**
         * @brief This variable represents the Control Instruction register of the Manchester Baby
         */
        int ci;

        /**
         * @brief This variable represents the Present Instruction register of the Manchester Baby
         */
        string pi;

        /**
         * @brief This variable represents the Accumulator register of the Manchester Baby
         */
        string acc;

        /**
         * @brief This string vector represents the store (memory) of the Manchester Baby
         */
        vector<string> store;

        /**
         * @brief Whether the simulator is ready to run
         */
        bool ready = false;


        /**
         * @brief Whether the simulator is done running a program
         */
        bool done = false;

        /**
         * @brief Whether to run the program continuously or step-by-step
         */
        bool step = true;

        /**
         * @brief Whether to show fetch-execute cycle explanations or not
         */
        bool info = true;

        /**
         * @brief The memory size of the simulator (in lines/addresses)
         */
        int memsize = 32;

        /**
         * @brief A string for the Simulator to store error messages in
         * 
         */
        string error = "";

    public:
        /**
         * @brief Construct a new Simulator object
         */
        Simulator();

        /**
         * @brief Sets up the Simulator object
         */
        void setup();

        /**
         * @brief Loads the program and validates it
         */
        bool loadProgram(string fileName);

        /**
         * @brief Runs the simulator with the settings set previously (only if ready == true)
         */
        void run();

        /**
         * @brief Increase the CI value by 1
         */
        void incrementCI();

        /**
         * @brief Gets the value at store index CI and loads it into PI
         */
        void fetch();

        /**
         * @brief Decodes the PI, fetches operand and executes the instruction specified
         */
        void decodeAndExecute();

        /**
         * @brief Display registers and stores
         */
        void display();

        /**
         * @brief Store the current memory and register values in a text file
         */
        void saveToFile();
};

// End of header guard
#endif