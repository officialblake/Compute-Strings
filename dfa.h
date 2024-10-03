// dfa.h
#ifndef DFA_H // include guard
#define DFA_H 
#include <iostream>
#include "state.h"

class DFA
{
private:
    std::vector<char> buffer;
    // Function prototypes for the different DFA states
    int state0(int n);  // Normal state, reading code
public:
    DFA() {}
    ~DFA() { delete this; };
    int begin(int n);
};


#endif /* DFA_H */
