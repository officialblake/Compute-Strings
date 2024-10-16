#include <iostream>
#include "dfa.h"
#include <numeric>
#include <gmpxx.h>
#include "bigWrapper.h"
#include <algorithm>
using namespace std;
// void countValidStrings(int n, mpz_t result) {
//     // Edge case: For strings of length <= 5, all combinations are valid
//     if (n <= 5) {
//         mpz_ui_pow_ui(result, 4, n);  // 4^n combinations since there are 4 characters
//         return;
//     }

//     // Pre-calculate all valid combinations of 6 characters over {a, b, c, d}
//     // that contain at least one 'a', 'b', 'c', and 'd'
//     std::vector<std::string> valid_states;
//     for (int i = 0; i < pow(4, 6); i++) {  // Iterate through all possible 6-character combinations
//         std::string window;
//         int temp = i;
//         for (int j = 0; j < 6; j++) {  // Convert the integer `i` to a 6-character string of {a, b, c, d}
//             window.push_back(static_cast<char>('a' + (temp % 4)));  // Mod by 4 to get one of the characters
//             temp /= 4;
//         }

//         // Check if the window contains at least one 'a', 'b', 'c', and 'd'
//         if (count(window.begin(), window.end(), 'a') > 0 &&
//             count(window.begin(), window.end(), 'b') > 0 &&
//             count(window.begin(), window.end(), 'c') > 0 &&
//             count(window.begin(), window.end(), 'd') > 0) {
//             valid_states.push_back(window);  // Only keep valid windows
//         }
//     }

//     // Create a map from each valid state (string) to an index for fast lookup
//     unordered_map<std::string, int> state_to_index;
//     for (int idx = 0; idx < valid_states.size(); idx++) {
//         state_to_index[valid_states[idx]] = idx;
//     }

//     // Initialize the DP table (Dynamic Programming table) to store counts of valid strings
//     // dp[length][state] holds the number of valid strings of a given length ending with a specific window
//     vector<vector<MpzWrapper>> dp(n + 1, vector<MpzWrapper>(valid_states.size()));

//     // Initialize the DP table for length 6 (base case)
//     for (int idx = 0; idx < valid_states.size(); idx++) {
//         mpz_set_ui(dp[6][idx].value, 1);  // Each valid state of length 6 has one valid string
//     }

//     // Populate the DP table for lengths from 7 to n
//     // Transition from one state (window) to another by sliding the window and appending a new character
//     for (int length = 7; length <= n; length++) {
//         for (int idx = 0; idx < valid_states.size(); idx++) {
//             string state = valid_states[idx];
//             for (char c : {'a', 'b', 'c', 'd'}) {  // Try appending each character to the current window
//                 string new_window = state.substr(1) + c;  // Slide the window by dropping the first character and adding a new one
//                 if (state_to_index.find(new_window) != state_to_index.end()) {
//                     mpz_add(dp[length][state_to_index[new_window]].value, dp[length][state_to_index[new_window]].value, dp[length - 1][idx].value);
//                 }
//             }
//         }
//     }

//     // Sum up all the valid strings of length n from all possible valid states
//     mpz_set_ui(result, 0);  // Initialize result to 0
//     for (int idx = 0; idx < valid_states.size(); idx++) {
//         mpz_add(result, result, dp[n][idx].value);
//     }
// }


int main(){
    mpz_t result;
    mpz_init(result);  
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    DFA *dfa = new DFA();
    mpz_class count = 0;
    std::cout << "Final count = ";
    dfa->generateDFA(result, n);
    std::cout << result;
    cout << endl;
    dfa = nullptr;
    delete dfa;
    return 0;
}