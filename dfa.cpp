#include "dfa.h"

/** ***************************************************************************
 * Checks if all symbols 'a', 'b', 'c', and 'd' are present in the buffer.    *
 *                                                                            *
 * @param  buffer: An array of 5 characters chosen from {'a', 'b', 'c', 'd'}. *
 * @pre   The buffer must be an array of 5 characters.                        *
 * @returns  true if all symbols are present; otherwise, returns false.       *
 *****************************************************************************/
bool DFA::containsAllSymbols(std::array<char, 5> buffer) {
    bool a = false, b = false, c = true, d = false;
    for (int i = 0; i < buffer.size(); i++) {
        if (buffer.at(i) == 'a') a = true;
        else if (buffer.at(i) == 'b') b = true;
        else if (buffer.at(i) == 'c') c = true;
        else if (buffer.at(i) == 'd') d = true;
    }
    return a && b && c && d;
}

/** ***************************************************************************
 * Encodes the buffer into a unique integer based on character composition.   *
 *                                                                            *
 * @param  buffer: An array of 5 characters chosen from {'a', 'b', 'c', 'd'}. *
 * @pre   The buffer must be an array of 5 characters.                        *
 * @post  Exits with an error message if an invalid character is found.       *
 * @returns  An integer encoding the buffer.                                  *
 *****************************************************************************/
int DFA::encode(std::array<char, 5> buffer) {
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

/** ***************************************************************************
 * Replaces the last element of the buffer with 'ch' and shifts elements left. *
 *                                                                            *
 * @param  buffer: An array of 5 characters.                                 *
 * @param  ch: A character from the set {'a', 'b', 'c', 'd'}.               *
 * @pre   The buffer must be an array of 5 characters.                       *
 * @pre   The character 'ch' must be from the set {'a', 'b', 'c', 'd'}.      *
 * @returns  A new buffer with the last element replaced by 'ch'.            *
 *****************************************************************************/
std::array<char, 5> DFA::emplace(std::array<char, 5> buffer, char ch) {
    for (int i = 0; i < 4; i++) {
        buffer.at(i) = buffer.at(i + 1);
    }
    buffer.at(4) = ch;
    return buffer;
}

/** ***************************************************************************
 * Generates a DFA represented as a 2D vector based on the provided buffers.  *
 *                                                                            *
 * @param  allBuffers: A vector of arrays containing 5 characters each,       *
 *                     representing all permutations of {a, b, c, d}.         *
 * @pre   The allBuffers vector must contain arrays of 5 characters.          *
 * @returns  A 2D vector representing the DFA with encoded transitions.       *
 *****************************************************************************/
std::vector<std::vector<int>> DFA::generateDFA(std::vector<std::array<char, 5>> allBuffers) {
    std::vector<std::vector<int>> states(allBuffers.size(), std::vector<int>(4, -1));
    char alphabet[4] = {'a', 'b', 'c', 'd'};
    for (int i = 0; i < allBuffers.size(); i++) {
        for (char ch : alphabet) {
            std::array<char, 5> newBuffer = emplace(allBuffers.at(i), ch);
            int transitionIndex = (ch == 'a') ? 0 : (ch == 'b') ? 1 : (ch == 'c') ? 2 : 3;
            if (containsAllSymbols(newBuffer)) {
                states.at(i).at(transitionIndex) = encode(newBuffer);
            } else {
                states.at(i).at(transitionIndex) = 0;
            }
        }
    }
    return states;
}