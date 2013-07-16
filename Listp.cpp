// Listp.cpp
// Mara Kim
//
// A tree object that stores a list

#include "Listp.h"

std::string Listp::print() const {
    std::stringstream ss;
    if(_head) {
        if(!_head->isAtom())
            ss << '{';
        ss << _head->print();
        if(!_head->isAtom())
            ss << '{';
    } else
        ss << "NIL";
    return ss.str();
}

