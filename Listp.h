// Listp.h
// Mara Kim
//
// A tree object that stores a list
// a la Lisp

#include "ListpCons.h"
#include <memory>
#include <string>

template <class T>
class Listp {
public:
    Listp();
    Listp(typename ListpCons<T>::ptr head);
    Listp(const typename ListpCons<T>::Atom& atom);
    void push_back(typename ListpCons<T>::ptr list);
    virtual std::string print() const;
private:
    typename ListpCons<T>::ptr _head;
};

