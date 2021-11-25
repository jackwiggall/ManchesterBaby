#include "Simulator.h"

int main() {

    Simulator sim;
    return 0;
}

Simulator::Simulator(){
    //
}

bool Simulator::setup(){
    //get memorySize
    //call load
    return false;
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
        //test push
}

void Simulator::decodeAndExecute() {

}

void Simulator::display() {
    //memory 32xnum grid
    //2 columns
    //coloured squares?
}