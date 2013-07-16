// ListpCons.h
// Mara Kim
//
// A recursive cons object 
// a la Lisp

#include <memory>
#include <string>
#include <sstream>

struct ListpCons {
public:
    typedef std::unique_ptr<ListpCons> ptr;
    struct Atom {
        std::string name;
        double value;
        bool null;

        Atom():
        name(),value(0),null(true) {}
        Atom(double value):
        name(),value(value),null(false) {}
        Atom(std::string name):
        name(name),value(0),null(true) {}
        Atom(std::string name,double value):
        name(name),value(value),null(false) {}

        std::string print() const {
            if(name.size())
                return name;
            else if(null)
                return "NIL";
            else {
                std::stringstream ss;
                ss << value;
                return ss.str();
            }
        }
    };

    ListpCons();
    ListpCons(ListpCons::ptr car, ListpCons::ptr cdr);
    ListpCons(double value);
    ListpCons(std::string name);
    ListpCons(std::string name,double value);
    ptr copy() const;
    virtual bool isAtom() const;
    virtual Atom atom() const;
    void insert(ListpCons::ptr list);
    void push_back(ListpCons::ptr list);
    virtual std::string print() const;
    // apply a scalar transformation to each atom
    // Func should take a ListpCons::Atom and return an ListpCons::Atom
    template<typename Func> void transform(Func func);
    // map each atom against a list
    // Func should take an ListpCons::Atom and return a ListpCons
    template<typename Func> void map(Func func);
    // TODO reduce the list
    // Func should take a ListpCons and return a ListpCons::Atom
    //template<typename Func> Atom reduce(Func func);
private:
    ListpCons::ptr _car, _cdr;
};

class ListpAtom: public ListpCons {
public:
    ListpAtom();
    ListpAtom(double value);
    ListpAtom(std::string name);
    ListpAtom(std::string name,double value);
    ListpAtom(Atom atom);
    ptr copy() const;
    bool isAtom() const;
    Atom atom() const;
    std::string print() const;
private:
    Atom _atom;
};

