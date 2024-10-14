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

void countStatesRecursive(std::vector<std::vector<int>>& states, std::vector<int>& prev, int n, int& count) {
    if (n == 5) {  // Base case: When n reaches 0, stop recursion
        return;
    }

    std::vector<int> next(prev.size(), 0);  // Create a new vector to track the next states

    // Iterate over each state in the current `prev` vector
    for (int i = 0; i < prev.size(); ++i) {
        if (prev[i] > 0) {  // Only process states that have valid transitions
            for (int j = 0; j < 4; ++j) {  // Iterate over alphabet {a, b, c, d}
                int nextState = states[i][j];  // Get the next state for the current state
                if (nextState > 0) {  // Valid transition
                    count++;  // Increment count for valid transitions
                    next[nextState] += prev[i];  // Accumulate counts into the next vector
                }
            }
        }
    }

    // Recursively call with the `next` vector for the next step
    countStatesRecursive(states, next, n - 1, count);
}

int countStates(std::vector<std::vector<int>> states, int n) {
    int m = states.size();
    std::vector<int> prev(m, 0);  // Vector to store the current state's transitions

    // Initialize the `prev` vector by checking if each state is accepting
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (states[i][j] > 0) {
                prev[i] = 1;  // Mark initial valid states
                break;
            }
        }
    }

    int count = 0;  // Initialize count of transitions
    countStatesRecursive(states, prev, n, count);  // Start recursive processing

    return count;
}


int main(){
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    DFA *dfa = new DFA();
    int count = 0;
    count = countStates(dfa->generateDFA(all_possible_buffers()), n);
    std::cout << "Final count = " << count << std::endl;
    delete dfa;
    return 0;
}