// Listp.h
// Mara Kim
//
// A tree object that stores a list
// a la Lisp

#include "ListpCons.h"
#include <memory>
#include <string>

class Listp {
public:
    Listp();
    Listp(ListpCons::ptr head);
    Listp(const ListpCons::Atom& atom);
    Listp(std::string name);
    Listp(double value);
    Listp(std::string name, double value);
    void push_back(ListpCons::ptr list);
    virtual std::string print() const;
private:
    ListpCons::ptr _head;
};

