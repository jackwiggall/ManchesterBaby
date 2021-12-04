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

//might need to add spaces between squares?
void Simulator::display() { 
    // Display stop lamp
        // Black or green/blue square depending on whether done is true or false
    if(done) {
        cout << BOLD(FCYN("Done?")) << "\t\t"<< FCYN(SQR) << endl; 
    }else {
        cout << BOLD(FCYN("Done?")) << "\t\t"<< FRED(SQR) << endl;
    }
    

    // Display values of registers in binary form (coloured squares) and in decimal (use binary::(un)signedBinaryToDecimal())
        // display CI (unsigned binary)
    int sqrLen = 5; //not sure what number
    string tempCi = binary::decimalToUnsignedBinary(ci,sqrLen);
    string ciVal;
    for (int i=0;i<sqrLen;i++) {
        if (tempCi.at(i)=='1') {
            ciVal += FCYN(SQR);
        }else {
            ciVal += SQR;
        }
    }cout << BOLD(FCYN("CI")) << "\t\t" << ciVal << "\t" << ci << endl;

        // display PI (unsigned binary)
    int piVal = binary::unsignedBinaryToDecimal(pi);
    string tempPi;
    if (pi.length()>0) {
        int piLen = pi.length(); //prevents compile warning
        for (int i=0;i<piLen;i++) {
            if (pi.at(i)=='1') {
                tempPi += FCYN(SQR);
            }else {
                tempPi += SQR;
            }
        }
    }else {
        for (int i=0;i<sqrLen;i++) {
            tempPi += SQR;
        }
    }
    cout << BOLD(FCYN("PI")) << "\t\t" << tempPi << "\t" << piVal << endl;


        // display accumulator (signed binary)
    int accVal = binary::signedBinaryToDecimal(acc);
    string tempAcc;
    if (acc.length()>0) {
        int accLen = acc.length(); //prevents compile warning
        for (int i=0;i<accLen;i++) {
            if (acc.at(i)=='1') {
                tempAcc += FCYN(SQR);
            }else {
                tempAcc += SQR;
            }
        }
    }else {
        for (int i=0;i<sqrLen;i++) {
            tempAcc += SQR;
        }
    }
    cout << BOLD(FCYN("Accumulator")) << "\t" << tempAcc << "\t" << accVal << endl; //idk

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


    // cout << "\n" << BOLD(FCYN("Memory")) << "\t\t" << value << endl; //store?
    // cout << BOLD(FCYN("MemoryVal")) << "\t" << &store << endl; //pointer of store
    // cout << BOLD(FCYN("RegisterVal")) << "\t" << &value << endl; //pointer of register
    // cout << BOLD(FCYN("I/O")) << "\t\t" << value << endl;
    // cout << BOLD(FCYN("STOP")) << endl;
}

