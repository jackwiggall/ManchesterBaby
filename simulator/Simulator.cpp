#include "Simulator.h"
#include "Colors.h"


int main() {

    Simulator sim;
    sim.display();
    return 0;
}

Simulator::Simulator(){
    // Initialise registers
    ci = 0;
    pi = "00000000000000000000000000000000";
    acc = "00000000000000000000000000000000";

    // Initialise memory
    store.assign(memsize, "00000000000000000000000000000000");
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
        cout << "Input not recognised or empty, explanations shown by default." << endl;
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
        cout << "Input not recognised or empty, program runs step-by-steo by default" << endl;
    }

    cin.ignore(1000, '\n'); //if invalid input clear buffer 

    //get memory size user input
    cout << "\nWhat would you like the memory size to be, standard is 32 (must be between 32 and 4096)?" << endl;
    cin >> memoryChoice;

    //validation for the memory size 
    if ((memoryChoice >= 32) && (memoryChoice <= 4096)) {
        memsize = memoryChoice;
        memory.assign(memsize,"00000000000000000000000000000000");
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
    ci++;
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
    int addr;
    if(opcode != "011" && opcode != "111"){
        // Calculate operand address length based on memory size
        int bits = ceil(log(memsize)/log(2));
        
        // Get operand address and convert into decimal
        address = instruction.substr(0,bits-1);
        addr = binary::unsignedBinaryToDecimal(address);

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
        store[addr] = acc;
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
    // Display stop lamp
        // Black or green/blue square depending on whether done is true or false

    // Display values of registers in binary form (coloured squares) and in decimal (use binary::(un)signedBinaryToDecimal())
        // display CI (unsigned binary)
        // display PI (unsigned binary)
        // display accumulator (signed binary)

    // Display memory
        // Loop through every line of vector (use vector iterator)
        // Display each line as binary (colour squared) and as a signed binary in decimal (binary::signedBinaryToDecimal(string))






    // Old code

    // int value = 0; //default value to be changed later once data is given

    // //outputs 0 if the strings pi and acc are empty
    // string piVal = pi;
    // if (pi=="") {
    //     piVal = "0";
    // }
    // string accVal = acc;
    // if (acc=="") {
    //     accVal = "0";
    // }


    // cout << "\n" << BOLD(FGRN("Memory")) << "\t\t" << value << endl; //store?
    // cout << BOLD(FGRN("MemoryVal")) << "\t" << &store << endl; //pointer of store
    // cout << BOLD(FGRN("RegisterVal")) << "\t" << &value << endl; //pointer of register
    // cout << BOLD(FGRN("CI")) << "\t\t" << ci << endl;
    // cout << BOLD(FGRN("PI")) << "\t\t" << piVal << endl;
    // cout << BOLD(FGRN("Accumulator")) << "\t" << accVal << endl; //idk
    // cout << BOLD(FGRN("I/O")) << "\t\t" << value << endl;
    // cout << BOLD(FGRN("STOP")) << endl;
}

