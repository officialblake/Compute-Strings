#include <iostream>
#include "dfa.h"
#include <numeric>
#include <gmpxx.h>
#include <cmath>
#include <array>
#include <vector>
/** ***************************************************************************
 * Generates all possible buffers of length 5 using the alphabet {a, b, c, d}.*
 *                                                                            *
 * @pre   None.                                                               *
 * @returns  A vector of arrays, each containing a valid buffer of characters.*
 *****************************************************************************/
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

/** ***************************************************************************
 * Recursively counts the valid states in the DFA.                            *
 *                                                                            *
 * @param  states: A vector of vectors containing integer states.             *
 * @param  current: A vector of mpz_class for current state counts.           *
 * @param  n:     An integer representing the number of remaining states.     *
 * @param  count: A reference to an mpz_class that will hold the final count. *
 * @pre   states must be a non-empty vector containing vectors of integers.   *
 * @pre   current must be a vector of mpz_class.                              *
 * @pre   n must be a non-negative integer.                                   *
 * @post  count is updated to reflect the total number of valid states.       *
 *****************************************************************************/
void countStatesRecursive(const std::vector<std::vector<int>>& states, std::vector<mpz_class>& current, int n, mpz_class& count) {
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
            count = 1;
            return; 
        default:
            break;  
    }

    std::vector<mpz_class> next(current.size(), 0);  

    for (int i = 0; i < current.size(); ++i) {
        if (current[i] > 0) { 
            for (int j = 0; j < 4; ++j) {  
                int nextState = states[i][j]; 
                if (nextState > 0) {  
                    next[nextState] += current[i]; 
                }
            }
        }
    }

    countStatesRecursive(states, next, n - 1, count);

    if (count <= 1024) {
        mpz_class sum = 0;
        for (const auto& elem : next) {
            sum += elem; 
        }
        count = sum;
    }
}

/** ***************************************************************************
 * Counts the valid states in the DFA.                                        *
 *                                                                            *
 * @param  states: A vector of vectors containing integer states.             *
 * @param  n:     An integer representing the number of remaining states.     *
 * @pre   states must be a non-empty vector containing vectors of integers.   *
 * @pre   n must be a non-negative integer.                                   *
 * @returns  The total count of valid states as an mpz_class.                 *
 *****************************************************************************/
mpz_class countStates(const std::vector<std::vector<int>>& states, int n) {
    int m = states.size();
    std::vector<mpz_class> current(m, 1);  

    for (int i = 0; i < m; ++i) {
        bool hasValidTransition = false;
        for (int j = 0; j < 4; ++j) {
            if (states[i][j] >= 0) {  
                hasValidTransition = true;
                break;
            }
        }
        if (!hasValidTransition) {
            current[i] = 0;  
        }
    }

    mpz_class count = 0; 
    countStatesRecursive(states, current, n, count);  
    return count; 
}
/** ***************************************************************************
 *                              Main Function                                 *   
 *****************************************************************************/
int main(){
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    if (n > 300 || n < 1) {
        std::cerr << "Error: n out of range. Enter a valid value (1-300).";
        exit(1);
    }

    DFA *dfa = new DFA();
    mpz_class count = 0;
    count = countStates(dfa->generateDFA(all_possible_buffers()), n);
    std::cout << "Final count = " << count << std::endl;
    delete dfa;
    dfa = nullptr;
    return 0;
}