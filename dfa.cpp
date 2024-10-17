// dfa.cpp
#include "dfa.h" 
#include "bigWrapper.h"
#include <map>

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
}

std::array<char, 5> DFA::emplace(std::array<char, 5> buffer, char ch) {
    // Shift characters to make room for the new one
    for (int i = 0; i < 4; i++) {
        buffer[i] = buffer[i + 1];
    }
    buffer[4] = ch;  // Add the new character at the end
    return buffer;
}

char DFA::getChar(int i){
    if (i == 0) {
        return 'a';
    } else if (i == 1) {
        return 'b';
    } else if(i == 2) {
        return 'c';
    } else if(i == 3) {
        return 'd';
    } 
    std::cerr << "Error: incompatible value passed to getChar(): " << i;
    exit(1);
}

void DFA::generateDFA(mpz_t result, int n) {
    int totalPermutations = pow(4, 5) + 1024;

    if (n <= 5) {
        mpz_ui_pow_ui(result, 4, n);
        return; 
    }

    std::vector<std::array<char, 5>> states;

    for (int i = 0; i < totalPermutations - 1024; i++) {
        std::array<char, 5> allCharacters;
        int ind = i;

        for (int j = 0; j < 5; j++) { 
            allCharacters[j] = getChar(ind % 4);
            ind /= 4;
        }
        states.push_back(allCharacters);
    }

    int m = states.size();
    
    // Create a 2D vector to hold MPZWrapper values
    std::vector<std::vector<MPZWrapper>> N(m, std::vector<MPZWrapper>(n + 1));      

    // // Initialize Nj(0)
     for (int i = 0; i < m; i++) {
        mpz_set_ui(N[i][0].value, 1);  // Nj(0) = 1 for all states, since all are valid
                             std::cout << "First val: " << N[0][0].value << std::endl;

    }

    // Compute Nj(n) using the recurrence relation
    for (int length = 1; length <= n; length++) {
        for (int i = 0; i < m; i++) {
            for (char ch : {'a', 'b', 'c', 'd'}) {  // For each character
                // Prepare a buffer to hold 5 characters
             std::array<char, 5> buffer = {states[i][1], states[i][2], states[i][3], states[i][4], ch};
                                               std::cout << "first: " << N[i][length - 1].value << std::endl;

                if (containsAllSymbols(buffer)){
                     mpz_add(N[encode(buffer)][length].value, N[encode(buffer)][length].value, N[i][length - 1].value);
                } else {
                      mpz_set_ui(N[encode(buffer)][length].value, 0);
                }
              
            }
        }
    }

    // Sum all Nj(n) for the final result
    mpz_set_ui(result, 0);  // Initialize result to 0
    for (int i = 0; i < N.size(); i++) {
        //std::cout << "val: "<< N[i][n].value;
        mpz_add(result, result, N[i][n].value); // Sum all accepted strings of length n
    }
}