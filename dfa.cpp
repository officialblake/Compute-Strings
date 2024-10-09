// dfa.cpp
#include "dfa.h" 

bool DFA::containsAllSymbols(std::array<char, 5> buffer){
    bool a, b, c, d;
    if (buffer.size() < 5){
        return true;
    } 
    for (int i = 0; i < buffer.size(); i++) {
        if (buffer.at(i) == 'a') a = true;
        else if (buffer.at(i) == 'b') a = true;
        else if (buffer.at(i) == 'c') a = true;
        else if (buffer.at(i) == 'd') a = true;
    }
    return a && b && c && d;
}

int DFA::encode(std::array<char, 5> buffer){
    int encoding = 0;
    for (int i = buffer.size() - 1; i <= 0; i--) {
        
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
}

std::array<char, 5> DFA::emplace(std::array<char, 5> buffer, char ch){
    if (buffer.size() < 5){
        buffer.back() = ch;
    } 
    for (int i = 0; i < 4; i++){
        buffer.at(i) = buffer.at(i + 1);
    }
    buffer.at(4) = ch;
    return buffer;
}

std::vector<std::vector<int>> DFA::generateDFA(std::vector<std::array<char, 5>> allBuffers){
    std::vector<std::vector<int>> states(allBuffers.size(), std::vector<int>(4, -1));
    char alphabet[4] = {'a', 'b', 'c', 'd'};
    for (int i = 0; i < allBuffers.size(); i++){
        for (char ch : alphabet) {
            std::array<char, 5> newBuffer = emplace(allBuffers.at(i), ch);
            int transitionIndex = (ch == 'a') ? 0 : (ch == 'b') ? 1 : (ch == 'c') ? 2 : 3;
            if (containsAllSymbols(newBuffer)){
                states.at(i).at(transitionIndex) = encode(newBuffer);
            } else {
                states.at(i).at(transitionIndex) = 0;
            }
        }
    }
    return states;
}