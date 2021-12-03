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
    
    //checks if ci is over memory capacity
    if (ci >=memsize)
    {
        throw invalid_argument("the Ci counter exceded memory size");
    }
    
    
  
    //use number to find line in store file
    pi = store[ci];
   
    

}

void Simulator::decodeAndExecute() {

}

void Simulator::display() {
    //memory 32xnum grid
    //2 columns
    //coloured squares?
}