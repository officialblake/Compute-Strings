// dfa.h
#ifndef DFA_H // include guard
#define DFA_H 
#include <iostream>
#include <gmpxx.h>

class DFA
{
private:
    // Function prototypes for the different DFA states
    bool containsAllSymbols(std::array<char, 6> buffer);
    int encode(std::array<char, 5> buffer);
    std::array<char, 5> emplace(std::array<char, 5> buffer, char ch);
    char getChar(int i);
public:
    void generateDFA(mpz_t result, int n);
    DFA() {};
    ~DFA() {};
};


#endif /* DFA_H */
