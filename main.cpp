#include <iostream>
#include "dfa.h"
#include <numeric>

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
void countStatesRecursive(const std::vector<std::vector<int>>& states, std::vector<int>& current, int n, int& count) {
    switch (n) {
        case 5:
            count = std::pow(4, 5);
            return;
        case 4:
            count = std::pow(4, 4);
            return;
        case 3:
            count = std::pow(4, 3);
            return;
        case 2:
            count = std::pow(4, 2);
            return;
        case 1:
            count = std::pow(4, 1);
            return;
        case 0:
            return;  // Base case: When n is 0, stop recursion
        default:
            break;  // Keep going
    }


    std::vector<int> next(current.size(), 0);  // Track the next states' counts

    // Iterate over each state in the current vector
    for (int i = 0; i < current.size(); ++i) {
        if (current[i] > 0) {  // Only process states with valid transitions
            for (int j = 0; j < 4; ++j) {  // Iterate over alphabet {a, b, c, d}
                int nextState = states[i][j];  // Get the next state for the current state
                if (nextState > 0) {  // Valid transition (assuming -1 is invalid state)
                    next[nextState] += current[i];  // Accumulate counts into the next vector
                }
            }
        }
    }

    // Recursively call with the next vector for the next step
    countStatesRecursive(states, next, n - 1, count);
    std::cout << " count is currently = " << count << std::endl;
    // Update the total count (number of accepted transitions)
    count += std::accumulate(next.begin(), next.end(), 0) - 1024;
}

int countStates(const std::vector<std::vector<int>>& states, int n) {
    int m = states.size();
    std::vector<int> current(m, 1);  // Initially set all states with 1 for uniform start

    // Initialize the `current` vector for valid starting states
    for (int i = 0; i < m; ++i) {
        bool hasValidTransition = false;
        for (int j = 0; j < 4; ++j) {
            if (states[i][j] >= 0) {  // Check if the state has a valid transition
                hasValidTransition = true;
                break;
            }
        }
        if (!hasValidTransition) {
            current[i] = 0;  // Mark state as invalid if it has no valid transitions
        }
    }

    int count = 0;  // Initialize count of transitions
    countStatesRecursive(states, current, n, count);  // Start recursive processing

    return count;  // Return the final count
}


int main(){
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    DFA *dfa = new DFA();
    int count = 0;
    count = countStates(dfa->generateDFA(all_possible_buffers()), n);
    std::cout << "Final count = " << count << std::endl;
    dfa = nullptr;
    delete dfa;
    return 0;
}