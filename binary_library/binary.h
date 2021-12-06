#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <cmath>
#include <vector>

namespace binary {

    int unsignedBinaryToDecimal(std::string binary);
    int signedBinaryToDecimal(std::string binary);

    std::string decimalToUnsignedBinary(int decimal, int size);
    std::string decimalToSignedBinary(int decimal, int size);

    std::string getTwosCompliment(std::string binary);

    std::string binaryAdd(std::string a, std::string b);
    std::string binarySubtract(std::string a, std::string b);

}

#endif