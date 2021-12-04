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
 *  Function sets up the simulator by setting the starting values (memory size and info)
 */
bool Simulator::setup(){
    char infoChoice;
    int memoryChoice;

    //get user input for if info should be displayed
    cout << "\nWould you like to display fetch execute explanation while running? [y/n]" << endl;
    cin >> infoChoice;

    //info validation
    if (infoChoice == 'y') {
        info = true;
    } else if (infoChoice == 'n') {
        info = false;
    } else {
        cout << "invalid input, set to true as default" << endl;
    }

    //get memory size user input
    cout << "What would you like the memory size to be, standard is 32 (must be between 1 and 64)?" << endl;
    cin >> memoryChoice;

    //validation for the memory size 
    if ((memoryChoice > 0) && (memoryChoice <= 64)) {
        memsize = memoryChoice;
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