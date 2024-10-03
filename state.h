// state.h
#ifndef STATE_H // include guard
#define STATE_H 
#include <iostream>

class State
{
private:
    int name;
    bool satisfiesA;
    bool satisfiesB;
    bool satisfiesC;
    bool satisfiesD;

    State *next;
    void setName(std::vector<char> &buffer);
    bool parseBuffer(char ch, std::vector<char> &buffer);
public:
    State(char ch, std::vector<char> &buffer);
    ~State() { delete this; };
    int getName() { return name; }

};

#endif /* STATE_H */
