// dfa.h
#ifndef DFA_H // include guard
#define DFA_H 
#include <iostream>

class DFA
{
private:
    // Function prototypes for the different DFA states
    int state0(int n);  // Normal state, reading code
public:
    DFA() {}
    ~DFA() { delete this; };
    int begin(int n) { return state0(n); }
};


#endif /* DFA_H */
