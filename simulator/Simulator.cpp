#include "Simulator.h"

int main() {

    Simulator sim;
    sim.setup();
    return 0;
}

Simulator::Simulator(){
    //
}

/**
 *  Function sets up the simulator by setting the starting values (memory size, info and step) and calls the load function.
 */
bool Simulator::setup(){
    string infoChoice;
    int memoryChoice;
    string stepChoice;
    std::vector<string> memory;

    //get user input for if info should be displayed
    cout << "\nWould you like to display fetch execute explanation while running? [y/n]" << endl;
    cin >> infoChoice;

    //info validation
    if (infoChoice == "y") {
        info = true;
    } else if (infoChoice == "n") {
        info = false;
    } else {
        cout << "invalid input, set to true as default" << endl;
    }

    cin.ignore(1000, '\n'); //if invalid input clear buffer 

    //get user input for if program should run step by step
    cout << "\nWould you like to run the program step by step or continuously? [s/c]" << endl;
    cin >> stepChoice;

    //step validation
    if (stepChoice == "s") {
        step = true;
    } else if (stepChoice == "c") {
        step = false;
    } else {
        cout << "invalid input, set to step by step as default" << endl;
    }

    cin.ignore(1000, '\n'); //if invalid input clear buffer 

    //get memory size user input
    cout << "\nWhat would you like the memory size to be, standard is 32 (must be between 32 and 4096)?" << endl;
    cin >> memoryChoice;

    //validation for the memory size 
    if ((memoryChoice >= 32) && (memoryChoice <= 4096)) {
        memsize = memoryChoice;
        memory.assign(memsize,"0");
    } else {
        cout << "invalid input, set to 32 as default" << endl;
    }

    //call load and check if successful
    if (loadProgram() == true);
        ready = true;
    return true;
}

bool Simulator::loadProgram(){
    return false;
}

void Simulator::run() {
    if (ready==true) {
        //loop?
        incrementCI();
        fetch();
        decodeAndExecute();
        display();
    }
}

void Simulator::incrementCI() {
    
}

void Simulator::fetch() {

}

void Simulator::decodeAndExecute() {

}

void Simulator::display() {
    //memory 32xnum grid
    //2 columns
    //coloured squares?
}