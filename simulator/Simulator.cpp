#include "Simulator.h"
#include "Colors.h"

int main() {

    Simulator sim;
    sim.display();
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

}

void Simulator::decodeAndExecute() {

}

void Simulator::display() {
    //memory 32xnum grid
    //2 columns
    //coloured squares?

    //display content shows memory, CI, PI, accum, STOP
    //Display is printed after each cycle
    //text, text-based graphics, colour?

    //each step in the fetch-dec-exe cycle the state of each part
    //of the BABY hardware, i.e displaying register values, memory values and I/O
    
    /**
     * int num = 3;
     * string output;
     * output += to_string(num);
     * cout << output << endl;**/

    int value = 0; //default value to be changed later once data is given

    //outputs 0 if the strings pi and acc are empty
    string piVal = pi;
    if (pi=="") {
        piVal = "0";
    }
    string accVal = acc;
    if (acc=="") {
        accVal = "0";
    }


    cout << "\n" << BOLD(FGRN("Memory")) << "\t\t" << value << endl; //store?
    cout << BOLD(FGRN("MemoryVal")) << "\t" << &store << endl; //pointer of store
    cout << BOLD(FGRN("RegisterVal")) << "\t" << &value << endl; //pointer of register
    cout << BOLD(FGRN("CI")) << "\t\t" << ci << endl;
    cout << BOLD(FGRN("PI")) << "\t\t" << piVal << endl;
    cout << BOLD(FGRN("Accumulator")) << "\t" << accVal << endl; //idk
    cout << BOLD(FGRN("I/O")) << "\t\t" << value << endl;
    cout << BOLD(FGRN("STOP")) << endl;
    
    //🔲 ⬜ ⬛ emoji idk
}