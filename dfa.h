// dfa.h
#ifndef DFA_H // include guard
#define DFA_H 
#include <iostream>
#include <cmath>
#include <array>
#include <vector>
class DFA
{
private:
    // Function prototypes for the different DFA states
    bool containsAllSymbols(std::array<char, 5> buffer);
    int encode(std::array<char, 5> buffer);
    std::array<char, 5> emplace(std::array<char, 5> buffer, char ch);
public:
    DFA() {}
    ~DFA() { delete this; };
    std::vector<std::vector<int>> generateDFA(std::vector<std::array<char, 5>> allBuffers);
};


#endif /* DFA_H */
