#include "Simulator.h"
#include <fstream>

int main() {
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

bool Simulator::loadProgram(string fileName){
    string line;
    //load in file
    ifstream reader(fileName);
    if (!reader) {
        return false;
    }
    //count lines
    int i = 0;
    while(getline(reader, line)) {
        if (line.length() >= 32) { //if line not 32 bits long then reject
            return false;
        }
        store.push_back(line); //add to store
        i++;
    }
    //check memory was big enough
    if (i >= memsize) {
        return false;
    } else {
        //fill remaining memory with 0s
        for (i; i < memsize; i++)
        {
            store.push_back("00000000000000000000000000000000");
        }
    }
    return true;
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