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
        while(!done){
            incrementCI();
            fetch();
            decodeAndExecute();
            display();
        }
    }
    else{
        // Display error message
    }
}

void Simulator::incrementCI() {
    
}

void Simulator::fetch() {
    
    //checks if ci is over memory capacity
    if (ci >=memsize)
    {
        throw invalid_argument("The CI counter exceeds the memory size of the computer.");
    }
    
    
  
    //use number to find line in store file
    pi = store[ci];
   
    

}

void Simulator::decodeAndExecute() {
    // Get instruction from register
    string instruction = pi;

    // Retrieve opcode
    string opcode = instruction.substr(13,3);

    // Do not fetch operand for CMP and STP instructions, as they are not required
    string address = "";
    string operand = "";
    if(opcode != "011" && opcode != "111"){
        // Calculate operand address length based on memory size
        int bits = ceil(log(memsize)/log(2));
        
        // Get operand address and convert into decimal
        address = instruction.substr(0,bits-1);
        int addr = binary::unsignedBinaryToDecimal(address);

        // Fetch operand from store
        operand = store[addr];
    }

    // Check opcodes in string representation to avoid unnecessary calculations

    // Jump to a memory location specified by the value at memory location specified by operand
    if(opcode == "000" /* 0 JMP */){
        ci = binary::unsignedBinaryToDecimal(operand);
        return;
    }

    // Jump Relative by adding the value at memoroy location specified by operand to CI
    if(opcode == "100" /* 1 JRP */){
        ci += binary::unsignedBinaryToDecimal(operand);
        return;
    }

    // Load negative of value at memoroy location specified by operand into accumulator
    if(opcode == "010" /* 2 LDN */){
        acc = binary::getTwosCompliment(operand);
        return;
    }

    // Store value in accumulator into memory location specified by operand
    if(opcode == "110" /* 3 STO */){
        acc = binary::getTwosCompliment(operand);
        return;
    }

    // Subtract value at memoroy location specified by operand from accumulator and store result in accumulator
    if(opcode == "001" || opcode == "101" /* 4,5 SUB */){
        acc = binary::binarySubtract(acc, operand);
    }

    // If value in accumulator is less than zero, increment CI by one
    if(opcode == "011" /* 6 CMP */){
        if(binary::signedBinaryToDecimal(acc) < 0){
            ci++;
        }
        return;
    }

    // Halt the program
    if(opcode == "111" /* 7 STP */){
        done = true;
        return;
    }
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

