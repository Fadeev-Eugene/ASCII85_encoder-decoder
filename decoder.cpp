#include "decoder.h"


void decoder(std::istream& cin, std::ostream& cout){
    std::vector<char> block;
    
    char ch; 
    while (cin.get(ch)){
        if (std::isspace(static_cast<unsigned char>(ch))) {
            continue;
        }

        if (ch == 'z'){
            if (block.empty()){
                cout.write("\0\0\0\0", 4);
                continue;
            } else {
                throw std::runtime_error("'z' in middle of block");        
            }
        }

        if ((ch < 33) or (ch > 117)){
            throw std::runtime_error("Invalid ASCII85 character: " + ch);         
        }
        
        block.push_back(ch);
       

        if (block.size() == 5){
            long num = 0; 
            for (int i = 0; i < 5; i++){
                int exp = std::pow(85, (4-i));
                num = num + static_cast<unsigned int>(block[i] - 33)*exp;
            }
            
            std::array<char, 4> nblock;
            
            for (int i = 0; i < 4; i++){
                int exp = std::pow(256, (3-i));
                unsigned int n = num / exp;
                num = num % exp;
                nblock[i] = static_cast<char>(n);
            } 
            
            cout.write(reinterpret_cast<const char*>(nblock.data()), 4);            

            block.clear();
        }
    }
    int size = block.size();
    if (size){
        while (block.size() < 5){
            block.push_back('u');        
        }

        long num = 0; 
        for (int i = 0; i < 5; i++){
            int exp = std::pow(85, (4-i));
            num = num + static_cast<unsigned int>(block[i] - 33)*exp;
        }
        
        std::array<unsigned char, 4> nblock;
        
        for (int i = 0; i < 4; i++){
            int exp = std::pow(256, (3-i));
            unsigned int n = num / exp;
            num = num % exp;
            nblock[i] = static_cast<char>(n);
        } 
        
        cout.write(reinterpret_cast<const char*>(nblock.data()), size - 1);     
    }
}
