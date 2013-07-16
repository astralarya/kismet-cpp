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
    virtual std::string print() const;
private:
    ListpCons::ptr _head;
};

