#include "binary.h"
#include <iostream>

namespace binary {

    int unsignedBinaryToDecimal(std::string binary){
        int decimal = 0;
        int length = binary.length();

        for(int i = 0; i < length; i++){
            if(binary[i] == '1'){
                decimal += pow(2,i);
            }
        }

        return decimal;
    }

    int signedBinaryToDecimal(std::string binary){
        if(binary.back() == '0'){
            return unsignedBinaryToDecimal(binary);
        }
        else{
            binary = getTwosCompliment(binary);
            return (unsignedBinaryToDecimal(binary) * -1);
        }
    }

    std::string decimalToUnsignedBinary(int decimal, int size){
        std::vector<int> array(size, 0);
        
        for(int i = 0; decimal > 0; i++){
            array[i] = decimal % 2;
            decimal /= 2;

            if(i == size-1){
                break;
            }
        }

        std::string binary = "";
        for(int i = 0; i < size; i++){
            binary = binary + std::to_string(array[i]);
        }

        return binary;
    }

    std::string decimalToSignedBinary(int decimal, int size){
        std::string binary = decimalToUnsignedBinary(abs(decimal), size);

        if(decimal >= 0){
            return binary;
        }
        else{
            binary = getTwosCompliment(binary);
            return binary;
        }
    }

    std::string binaryAdd(std::string a, std::string b){
        if(a.length() < b.length()){
            a.insert(a.end(), b.length()-a.length(), '0');
        }
        if(b.length() < a.length()){
            b.insert(b.end(), a.length()-b.length(), '0');
        }

        int size = a.length(); 

        std::vector<int> array(size, 0);
        int carry = 0;

        for(int i = 0; i < size; i++){
            int x, y;
            if(a[i] == '1'){
                x = 1;
            }
            else{
                x = 0;
            }
            if(b[i] == '1'){
                y = 1;
            }
            else{
                y = 0;
            }

            array[i] = (x ^ y) ^ carry;
            carry = (x & y) | (x & carry) | (y & carry);
        }

        std::string binary = "";
        for(int i = 0; i < size; i++){
            binary = binary + std::to_string(array[i]);
        }

        return binary;
    }

    std::string binarySubtract(std::string a, std::string b){
        b = getTwosCompliment(b);
        return binaryAdd(a, b);
    }

    std::string getTwosCompliment(std::string binary){
        for(int i = 0; i < (int) binary.length(); i++){
            if(binary[i] == '0'){
                binary[i] = '1';
            }
            else{
                binary[i] = '0';
            }
        }
        binary = binaryAdd(binary, "1");
        return binary;
    }

}

int main(){
    std::cout << binary::decimalToUnsignedBinary(47,8) << std::endl;
    std::cout << binary::decimalToSignedBinary(47,8) << std::endl;
    std::cout << binary::decimalToSignedBinary(-47,8) << std::endl;

    std::cout << binary::unsignedBinaryToDecimal("11110100") << std::endl;
    std::cout << binary::signedBinaryToDecimal("11110100") << std::endl;
    std::cout << binary::signedBinaryToDecimal("10001011") << std::endl;

    std::cout << binary::binaryAdd("11110100","11110100") << std::endl;
    std::cout << binary::binarySubtract("11110100","11110100") << std::endl;
}