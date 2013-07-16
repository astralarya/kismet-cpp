// ListpCons.cpp
// Mara Kim
//
// A recursive cons object 
// a la Lisp

#include "ListpCons.h"

template <class T>
ListpCons<T>::ListpCons():
_car(), _cdr() {}

template <class T>
ListpCons<T>::ListpCons(ListpCons::ptr car, ListpCons::ptr cdr):
_car(std::move(car)), _cdr(std::move(_cdr)) {}

template <class T>
ListpCons<T>::ListpCons(const ListpCons::Atom& atom):
_car(new ListpAtom<T>(atom)), _cdr() {}

template <class T>
typename ListpCons<T>::ptr ListpCons<T>::copy() const {
    return ListpCons::ptr(new ListpCons(_car->copy(),_cdr->copy()));
}

template <class T>
bool ListpCons<T>::isAtom() const {
    return false;
}

template <class T>
typename ListpCons<T>::Atom ListpCons<T>::atom() const {
    return Atom();
}

template <class T>
void ListpCons<T>::insert(ListpCons<T>::ptr list) {
    _cdr = ListpCons::ptr(new ListpCons(std::move(list),std::move(_cdr)));
}

template <class T>
void ListpCons<T>::push_back(ListpCons<T>::ptr list) {
    if(!_cdr)
        _cdr = ListpCons::ptr(new ListpCons(std::move(list),std::move(_cdr)));
    else
        _cdr->push_back(std::move(list));
}

template <class T>
std::string ListpCons<T>::print() const {
    std::stringstream ss;
    if(_car) {
        if(!_car->isAtom())
            ss << '{';
        ss << _car->print();
        if(!_car->isAtom())
            ss << '{';
    } else
        ss << "NIL";
    if(_cdr)
        ss << ',' << _cdr->print();
    return ss.str();
}

template <class T>
template<typename Func>
void ListpCons<T>::transform(Func func) {
    if(_car)
        if(_car->isAtom())
           _car = typename ListpCons<T>::ptr(new ListpAtom<T>(func(_car->atom())));
        else
           _car->transform(func);
    if(_cdr)
        _cdr->transform(func);
}

template <class T>
template<typename Func>
void ListpCons<T>::map(Func func) {
    if(_car)
        if(_car->isAtom())
           _car = ListpCons::ptr(func(_car->atom()));
        else
           _car->map(func);
    if(_cdr)
        _cdr->map(func);
}

/* TODO
template<typename Func>
ListpCons::Atom ListpCons::reduce(Func func) {
}
*/

template <class T>
ListpAtom<T>::ListpAtom():
ListpCons<T>(), _atom() {}

template <class T>
ListpAtom<T>::ListpAtom(typename ListpCons<T>::Atom atom):
ListpCons<T>(), _atom(atom) {}

template <class T>
typename ListpCons<T>::ptr ListpAtom<T>::copy() const {
    return ListpCons<T>::ptr(new ListpAtom<T>(_atom));
}

template <class T>
bool ListpAtom<T>::isAtom() const {
    return true;
}

template <class T>
typename ListpCons<T>::Atom ListpAtom<T>::atom() const {
    return _atom;
}

template <class T>
std::string ListpAtom<T>::print() const {
    return _atom.print();
}
