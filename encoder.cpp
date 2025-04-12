#include "encoder.h"


void encoder(std::istream& cin, std::ostream& cout){
    std::array<char, 4> block;
    const std::array<int, 5> powers = { 52200625, 614125, 7225, 85, 1 };
    while (true){
        cin.read(reinterpret_cast<char*>(block.data()), 4);
        int count = cin.gcount();

        if (count == 0){ break; }
        if (count < 4){
            for (int i = 0; i < (4-count); i++){
                block[3-i] = '\0';
            }
        }
        
        long num = 0;   
        for (char c : block){
            num = num * 256 + static_cast<unsigned int>(c);
        }      
        
        if (num == 0 && count == 4){
            cout.put('z');
            continue;
        }

        std::array<char, 5> nblock;

        for (int i = 0; i < 5; ++i) {
            unsigned int n = num / powers[i];
            num %= powers[i];
            nblock[i] = static_cast<char>(n + 33);
        }
        
        cout.write(reinterpret_cast<const char*>(nblock.data()), 1 + count);
    }    
}
