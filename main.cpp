#include <iostream>
#include "dfa.h"

std::vector<std::array<char, 5>> all_possible_buffers() {
    std::vector<std::array<char, 5>> buffers;
    char alphabet[4] = {'a', 'b', 'c', 'd'};

     for (int length = 1; length <= 5; length++) {
        int num_combinations = std::pow(4, length);
        
        for (int i = 0; i < num_combinations; i++) {
            std::array<char, 5> buffer; 
            int temp = i;

            for (int j = length - 1; j >= 0; j--) {
                buffer[j] = alphabet[temp % 4];
                temp /= 4;
            }
            buffers.push_back(buffer);
        }
    }
    return buffers;
}

int countStates(std::vector<std::vector<int>> states, int n){
    return 0;
}



int main(){
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    DFA *dfa = new DFA();
    dfa->generateDFA(all_possible_buffers());
    return 0;
}