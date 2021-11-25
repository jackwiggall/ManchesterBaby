#include "Simulator.h"

int main() {

    Simulator sim;
    return 0;
}

Simulator::Simulator(){
    //
}

bool Simulator::setup(){
    return false;
}

bool Simulator::loadProgram(){
    return false;
}

void Simulator::run() {
    if (ready==true) {
        
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

}