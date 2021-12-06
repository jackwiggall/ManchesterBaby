/**
 * @file Simulator.cpp
 * @authors [Group 1] Elliot Scott (2413916), Ross Coombs (2410466), Heather Currie (2411616), Jack Wiggall (2413924), Kai Uerlichs (2421101)
 *
 * @brief The source code for the Simulator class, representing a functionally expanded model of the Manchester SSEM (Baby)
 */

// Necessary includes
#include "Simulator.h"
#include "Colors.h"
#include "helpers.h"

/**
 * @brief Construct a new Simulator object
 */
Simulator::Simulator(){
    // Initialise registers
    ci = 0;
    pi = "00000000000000000000000000000000";
    acc = "00000000000000000000000000000000";

    // Initialise memory
    store.assign(memsize, "00000000000000000000000000000000");
}

/**
 * @brief Sets up the Simulator object
 */
void Simulator::setup(){
    // Clear the screen before setup
    helpers::clearScreen();

    // Declare local helpers
    string infoChoice;
    string stepChoice;
    string memoryChoice;
    string filename;

    cout << FCYN("\n█▀ █▀▀ ▀█▀ █ █ █▀█") << endl;
    cout <<   FCYN("▄█ ██▄  █  █▄█ █▀▀\n") << endl;

    // Prompt user about fetch-execute explanations
    cout << FCYN("\n[SETUP] ") << "Would you like to display fetch execute explanation while running? [y/n]" << endl;
    cin >> infoChoice;

    // Clear the input buffer to remove any pending tokens
    cin.ignore(1000, '\n');

    // Validate input and toggle info mode
    if (infoChoice == "y") {
        info = true;
    } else if (infoChoice == "n") {
        info = false;
    } else {
        cout << "Input not recognised or empty, explanations shown by default." << endl;
    }

    // Prompt user about step-by-step or continous mode
    cout << FCYN("\n[SETUP] ") << "Would you like to run the program step by step or continuously? [s/c]" << endl;
    cin >> stepChoice;

    // Clear the input buffer to remove any pending tokens
    cin.ignore(1000, '\n');

    // Validate input and toggle step mode
    if (stepChoice == "s") {
        step = true;
    } else if (stepChoice == "c") {
        step = false;
    } else {
        cout << "Input not recognised or empty, program runs step-by-steo by default" << endl;
    }

    // Prompt user for memory size
    cout << FCYN("\n[SETUP] ") << "What would you like the memory size to be, standard is 32 (must be between 32 and 4096)?" << endl;
    cin >> memoryChoice;

    // Clear the input buffer to remove any pending tokens
    cin.ignore(1000, '\n');

    int memory = 32;
    try{
        memory = stoi(memoryChoice);
    }
    catch(const invalid_argument &e){
        memory = -1;
    }

    // Validate input and initialise memory store
    if ((memory >= 32) && (memory <= 4096)) {
        memsize = memory;
        store.assign(memsize,"00000000000000000000000000000000");
    } else {
        cout << "Input is not valid, memory size set to default of 32 lines" << endl;
    }

    // Prompt user for filename
    cout << FCYN("\n[SETUP] ") << "Please enter the path of the machine code file:" << endl;
    cin >> filename;

    // Clear the input buffer to remove any pending tokens
    cin.ignore(1000, '\n'); 

    // Load the program and set ready 
    if (loadProgram(filename) == true){
        ready = true;
    }
}

/**
 * @brief Loads the program and validates it
 */
bool Simulator::loadProgram(string fileName){
    // Declare local variables
    string line;

    // Load file
    ifstream reader(fileName);
    
    // Return failed if file could not be read
    if (!reader) {
        error = "The file does not exist or could not be opened. Verify the filename is valid and that the file is not currenly used by any other program.";
        return false;
    }

    // Declare line counter
    int i = 0;

    // Loop through lines of file
    while(getline(reader, line)) {
        // Discard over-length characters
        line = line.substr(0,32);

        // Return failed if lines are not of valid length
        if (line.length() < 32) { 
            error = "The machine code file includes lines of invalid length. Please supply a valid machine code file.";
            return false;
        }

        // Attempt to push line to store
        try{
            store.at(i) = line; //add to store
        }
        // Return failed if too many lines in input file
        catch(const std::out_of_range& err){
            error = "The machine code file is larger than the memory space declared for this Simulator instance. Please declare more memory or supply a shorter machine code file.";
            return false;
        }

        // Incremement counter
        i++;
    }

    // Return successful
    return true;
}

/**
 * @brief Runs the simulator with the settings set previously (only if ready == true)
 */
void Simulator::run() {
    // Verify that the Simulator was correctly initiated
    if (ready==true) {
        // Loop through the fetch-execute cycle while the program is not completed yet
        while(!done){
            // Clear the screen
            helpers::clearScreen();

            // Fetch-execute operations
            incrementCI();
            fetch();
            decodeAndExecute();

            // If step-by-step execution is requested, display everything
            if(step == true){
                display();
                helpers::waitForInput();
            }
        }

        // If step-by-step execution was not requested, only display after execution
        if(step == false){
            display();
            helpers::waitForInput();
        }
    }
    // If the Simulator was not initiated correcly, send error
    else{
        // Clear the screen
        helpers::clearScreen();

        // Print large font
        cout << BOLD(FRED("\n█▀█ █▀█ █▀█ █▀     █▀ █▀█ █▀▄▀█ █▀▀ ▀█▀ █ █ █ █▄ █ █▀▀   █ █ █ █▀▀ █▄ █ ▀█▀   █ █ █ █▀█ █▀█ █▄ █ █▀▀   ▀ ▄▀")) << endl;
        cout <<   BOLD(FRED("█▄█ █▄█ █▀▀ ▄█ █   ▄█ █▄█ █ ▀ █ ██▄  █  █▀█ █ █ ▀█ █▄█   ▀▄▀▄▀ ██▄ █ ▀█  █    ▀▄▀▄▀ █▀▄ █▄█ █ ▀█ █▄█   ▄ ▀▄\n")) << endl << endl;
        
        // Print error message
        cout << "The Simulator instance you requested could not be set up, due to the following error:" << endl;
        cout << error << endl;

        // Press enter to continue
        helpers::waitForInput();
    }
}

/**
 * @brief Increase the CI value by 1
 */
void Simulator::incrementCI() {
    ci++;
}

/**
 * @brief Gets the value at store index CI and loads it into PI
 */
void Simulator::fetch() {
    // Checks if ci is over memory capacity
    if (ci >=memsize){
        throw invalid_argument("The CI counter exceeds the memory size of the computer.");
    }
    
    // Use number to find line in store vector
    pi = store[ci];
}

/**
 * @brief Decodes the PI, fetches operand and executes the instruction specified
 */
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

/**
 * @brief Display registers and stores
 */
void Simulator::display() { 
    // Register size
    int sqrLen = 32; 

    // Display stop lamp
    if(done) {
        cout << BOLD(FCYN("STOP")) << "\t\t"<< FCYN(SQR) << endl; 
    }else {
        cout << BOLD(FCYN("STOP")) << "\t\t"<< FBLK(SQR) << endl;
    }
    

    // Display values of registers in binary form (coloured squares) and in decimal (use binary::(un)signedBinaryToDecimal())    
    
    // Output CI
    string tempCi = binary::decimalToUnsignedBinary(ci,sqrLen);
    string ciSqr; //squares of ci
    for (int i=0;i<sqrLen;i++) {
        if (tempCi.at(i)=='1') {
            ciSqr += FCYN(SQR);
        }
        else {
            ciSqr += FBLK(SQR);
        } 
        ciSqr += " ";
    }
    cout << BOLD(FCYN("CI")) << "\t\t" << ciSqr << "\t" << ci << endl;

    // Output PI
    int piVal = binary::unsignedBinaryToDecimal(pi);
    string piSqr; //squares of pi
    if (pi.length()>1) { //string validation
        int piLen = pi.length(); //prevents compile warning
        for (int i=0;i<piLen;i++) {
            if (pi.at(i)=='1') {
                piSqr += FCYN(SQR);
            }
            else {
                piSqr += FBLK(SQR);
            }
            piSqr += " ";
        }
    }
    else {
        for (int i=0;i<sqrLen;i++) {
            piSqr += FBLK(SQR);
            piSqr += " ";
        }
    }
    cout << BOLD(FCYN("PI")) << "\t\t" << piSqr << "\t" << piVal << endl;


    // Output accumulator
    int accVal = binary::signedBinaryToDecimal(acc);
    string accSqr; //squares of acc
    if (acc.length()>1) { //string validation
        int accLen = acc.length(); //prevents compile warning
        for (int i=0;i<accLen;i++) {
            if (acc.at(i)=='1') {
                accSqr += FCYN(SQR);
            }
            else {
                accSqr += FBLK(SQR);
            }
            accSqr += " ";
        }
    }
    else {
        for (int i=0;i<sqrLen;i++) {
            accSqr += FBLK(SQR);
            accSqr += " ";
        }
    }
    cout << BOLD(FCYN("Accumulator")) << "\t" << accSqr << "\t" << accVal << endl;

    // Display memory
    // Display each line as binary (colour squared) and as a signed binary in decimal (binary::signedBinaryToDecimal(string))
    if (!store.empty()) {
        cout << BOLD(FCYN("\nStore")) << endl;
        for (int i=0;i<memsize;i++) {
            int mem = binary::signedBinaryToDecimal(store.at(i));
            string memSqr;
            int memLen = store.at(i).length(); //prevents compile warning
            if (memLen>1) { //string validation
                    for (int j=0;j<memLen;j++) {
                        if (store.at(i).at(j)=='1') {
                            memSqr += FCYN(SQR);
                        }
                        else {
                            memSqr += FBLK(SQR);
                        }
                        memSqr += " ";
                    }
                }
                else {
                    for (int j=0;j<memLen;j++) {
                        memSqr += FBLK(SQR);
                        memSqr += " ";
                    }
                }
            string valid = FCYN("Line ");
            valid += to_string(i);
            cout << valid << "\t\t" << memSqr << "\t" << mem << endl;
        }
    }
}

