#include <iostream>
#include "dfa.h"

std::vector<std::array<char, 5>> all_possible_buffers() {
    std::vector<std::array<char, 5>> buffers;
    char alphabet[4] = {'a', 'b', 'c', 'd'};
    int length = 5;
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

    return buffers;
}

int verifyDFA(std::vector<std::vector<int>> states, int n){
    int count = 0;
    for (int i = 0; i < states.size(); i++) {
        for (int j = 0; j < 4; j++) {
            
            if (states[i][j] > 0) {
                count++;
            }
            std::cout << "i = " << i << " j = " << j << " next state = " << states[i][j] << std::endl;
        }
    }
    std::cout << "states w trans = " << count << std::endl;
    return 0;
}

int countStates(std::vector<std::vector<int>> states, int n, int count) {
    if (n == 5) {  // Base case: When n is 0, stop recursion
        return count;
    }
    count = 0;
    std::vector<int> nextStates;
    std::cout << "size of state vec " << states.size() << std::endl;
    // Process the current states and transition to next states
    count = 0;
    for (int i = 0; i < states.size(); i++) {
        for (int j = 0; j < 4; j++) {  // Iterate over alphabet {a, b, c, d}
            if (states[i][j] > 0) {  // Valid transition
                count++;  // Increment count for each valid transition
                nextStates.push_back(states[i][j]);  // Track next states
            }
            //std::cout << "i = " << i << " j = " << j << " next state = " << states[i][j] << std::endl;
        }
    }

    // Create a new vector of next states and call recursively
    std::vector<std::vector<int>> nextStatesVector(nextStates.size(), std::vector<int>(4));
    for (int i = 0; i < nextStates.size(); ++i) {
        nextStatesVector[i] = states[nextStates[i]];
    }

    return countStates(nextStatesVector, n - 1, count);
}

int main(){
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    DFA *dfa = new DFA();
    int count = 0;
    count = countStates(dfa->generateDFA(all_possible_buffers()), n, count);
    std::cout << "Final count = " << count << std::endl;
    delete dfa;
    return 0;
}