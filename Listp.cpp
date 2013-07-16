// Listp.cpp
// Mara Kim
//
// A tree object that stores a list

#include "Listp.h"

template <class T>
Listp<T>::Listp():
_head() {}

template <class T>
Listp<T>::Listp(typename ListpCons<T>::ptr head):
_head(std::move(head)) {}

template <class T>
Listp<T>::Listp(const typename ListpCons<T>::Atom& atom):
_head(new ListpCons<T>(atom)) {}

template <class T>
void Listp<T>::push_back(typename ListpCons<T>::ptr list) {
    _head->push_back(std::move(list));
}

template <class T>
std::string Listp<T>::print() const {
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

