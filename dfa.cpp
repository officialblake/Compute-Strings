// dfa.cpp
#include "dfa.h" 

bool DFA::containsAllSymbols(std::array<char, 5> buffer){
    bool a=false, b=false, c=false, d=false;
    for (int i = 0; i < buffer.size(); i++) {
        if (buffer.at(i) == '\0') return true;
        else if (buffer.at(i) == 'a') a = true;
        else if (buffer.at(i) == 'b') b = true;
        else if (buffer.at(i) == 'c') c = true;
        else if (buffer.at(i) == 'd') d = true;
    }
    return a && b && c && d;
}

int DFA::encode(std::array<char, 5> buffer){
    int encoding = 0;
    for (int i = buffer.size() - 1; i >= 0; i--) {
        
        if (buffer.at(i) == 'a') {
            encoding += (0 * static_cast<int>(std::pow(4, 4 - i)));
        } else if (buffer.at(i) == 'b') {
            encoding += (1 * static_cast<int>(std::pow(4, 4 - i)));
        } else if (buffer.at(i) == 'c') {
            encoding += (2 * static_cast<int>(std::pow(4, 4 - i)));
        } else if (buffer.at(i) == 'd') {
            encoding += (3 * static_cast<int>(std::pow(4, 4 - i)));
        } else {
            std::cerr << "Unidentified character: " << buffer.at(i) << " Exiting...";
            exit(1);
        }
    }
    return encoding;
}ss
mpz_class DFA::generateDFA(mpz_t result, int n){
    if (n <= 5) {
        mpz_ui_pow_ui(result, 4, n); 
    }
    std::vector<std::array<char, 5>> valid_states;

    for (int i = 0; i < pow(4, 6); i++) {
        std::array<char, 5> tempBuffer;
        int ind = 0;
        for (int j = 0; j < 6; j++) {  // Convert the integer `i` to a 6-character string of {a, b, c, d}
            tempBuffer[j] = static_cast<char>('a' + (ind % 4));
            ind /= 4;
        }
        if (containsAllSymbols(tempBuffer)) {
            valid_states.push_back(tempBuffer);
        }
    }

    return 0;
}