#include <iostream>
#include <string>
#include "encoder.h"
#include "decoder.h"

int main(int argc, char* argv[]){
    if (argc > 2){
        throw std::runtime_error("Wrong syntax. Correct one 'ascii85 [-e/-d]'");
    } else if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "-e"){
            encoder(std::cin, std::cout);
        } else if (arg == "-d") {
            decoder(std::cin, std::cout);
        } else {
            throw std::runtime_error("Unknown argument " + arg);        
        }
    } else {
        encoder(std::cin, std::cout);
    }
    return 0;
}
