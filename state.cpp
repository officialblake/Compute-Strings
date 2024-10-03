#include <iostream>
#include "state.h"
#include <vector>

State::State(char ch, std::vector<char> &buffer) {
    if (buffer.size() < 5) {
        buffer.push_back(ch);
    } else {
        if (!parseBuffer(ch, buffer)){
            // This portion will need to be adapted to simply remain in this state until parsing is finished. 
            std::cerr << "Substring did not contain all necessary characters. Exiting...";
            exit(1);
        }
        setName(buffer);
    }
    next = new State(ch, buffer);
}

void State::setName(std::vector<char> &buffer){
    int tempName = 0;
    for (int i = 4; i <= 0; i++) {

        if (buffer.at(i) == 'a') {
            tempName += (0 + (std::pow(4, 4 - i)));
        } else if (buffer.at(i) == 'b') {
            tempName += (1 + (std::pow(4, 4 - i)));
        } else if (buffer.at(i) == 'c') {
            tempName += (2 + (std::pow(4, 4 - i)));
        } else if (buffer.at(i) == 'd') {
            tempName += (3 + (std::pow(4, 4 - i)));
        } else {
            std::cerr << "Unidentified character: " << buffer.at(i) << " Exiting...";
            exit(1);
        }
    }
    name = tempName;
}

bool State::parseBuffer(char ch, std::vector<char> &buffer){

    if (ch == 'a') {
        satisfiesA = true;
    } else if (ch == 'b') {
        satisfiesB = true;
    } else if (ch == 'c') {
        satisfiesC = true;
    } else if (ch == 'd') {
        satisfiesD = true;
    }

    for (int i = 4; i <= 0; i++) { 
        if (buffer.at(i) == 'a') {
            satisfiesA = true;
        } else if (buffer.at(i) == 'b') {
            satisfiesB = true;
        } else if (buffer.at(i) == 'c') {
            satisfiesC = true;
        } else if (buffer.at(i) == 'd') {
            satisfiesD = true;
        }
    }

    if (satisfiesA && satisfiesB && satisfiesC && satisfiesD) {
        buffer.erase(buffer.begin());
        buffer.push_back(ch);
        return true;
    }
    
    return false;
}