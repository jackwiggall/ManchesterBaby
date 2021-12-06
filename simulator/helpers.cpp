#include <iostream>
using namespace std;

namespace helpers {
    void clearScreen(){
        cout << "\033[2J\033[1;1H";
    }

    void waitForInput(){
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}