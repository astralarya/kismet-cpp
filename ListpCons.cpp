// ListpCons.cpp
// Mara Kim
//
// A recursive cons object 
// a la Lisp

#include "ListpCons.h"

ListpCons::ListpCons():
_car(), _cdr() {}

ListpCons::ListpCons(ListpCons::ptr car, ListpCons::ptr cdr):
_car(std::move(car)), _cdr(std::move(_cdr)) {}

ListpCons::ListpCons(const ListpCons::Atom& atom):
_car(new ListpAtom(atom)), _cdr() {}

ListpCons::ListpCons(double value):
_car(new ListpAtom(value)), _cdr() {}

ListpCons::ListpCons(std::string name):
_car(new ListpAtom(name)), _cdr() {}

ListpCons::ListpCons(std::string name,double value):
_car(new ListpAtom(name,value)), _cdr() {}

ListpCons::ptr ListpCons::copy() const {
    return ListpCons::ptr(new ListpCons(_car->copy(),_cdr->copy()));
}

bool ListpCons::isAtom() const {
    return false;
}

ListpCons::Atom ListpCons::atom() const {
    return Atom();
}

void ListpCons::insert(ListpCons::ptr list) {
    _cdr = ListpCons::ptr(new ListpCons(std::move(list),std::move(_cdr)));
}

void ListpCons::push_back(ListpCons::ptr list) {
    if(!_cdr)
        _cdr = ListpCons::ptr(new ListpCons(std::move(list),std::move(_cdr)));
    else
        _cdr->push_back(std::move(list));
}

std::string ListpCons::print() const {
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

template<typename Func>
void ListpCons::transform(Func func) {
    if(_car)
        if(_car->isAtom())
           _car = ListpCons::ptr(new ListpAtom(func(_car->atom())));
        else
           _car->transform(func);
    if(_cdr)
        _cdr->transform(func);
}

template<typename Func>
void ListpCons::map(Func func) {
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

ListpAtom::ListpAtom():
ListpCons(), _atom() {}

ListpAtom::ListpAtom(double value):
ListpCons(), _atom(value) {}

ListpAtom::ListpAtom(std::string name):
ListpCons(), _atom(name) {}

ListpAtom::ListpAtom(std::string name,double value):
ListpCons(), _atom(name,value) {}

ListpAtom::ListpAtom(ListpCons::Atom atom):
ListpCons(), _atom(atom) {}

ListpCons::ptr ListpAtom::copy() const {
    return ListpCons::ptr(new ListpAtom(_atom));
}

bool ListpAtom::isAtom() const {
    return true;
}

ListpCons::Atom ListpAtom::atom() const {
    return _atom;
}

std::string ListpAtom::print() const {
    return _atom.print();
}
