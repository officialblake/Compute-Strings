#include <iostream>
#include "dfa.h"

int main(){
    int n;
    std::cout << "Enter an integer (1 - 300).\n n = ";
    std::cin >> n;

    DFA *dfa = new DFA();

    std::cout << dfa->begin(n);
    return 0;
}