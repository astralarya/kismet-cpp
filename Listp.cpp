// Listp.cpp
// Mara Kim
//
// A tree object that stores a list

#include "Listp.h"

Listp::Listp():
_head() {}

Listp::Listp(ListpCons::ptr head):
_head(std::move(head)) {}

Listp::Listp(const ListpCons::Atom& atom):
_head(new ListpCons(atom)) {}

Listp::Listp(std::string name):
_head(new ListpCons(name)) {}

Listp::Listp(double value):
_head(new ListpCons(value)) {}

Listp::Listp(std::string name, double value):
_head(new ListpCons(name,value)) {}

void Listp::push_back(ListpCons::ptr list) {
    _head->push_back(std::move(list));
}

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

