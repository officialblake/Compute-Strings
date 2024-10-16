// dfa.h
#ifndef DFA_H // include guard
#define DFA_H 
#include <iostream>
#include <gmpxx.h>

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
    mpz_class generateDFA(mpz_t result, int n);
};


#endif /* DFA_H */
