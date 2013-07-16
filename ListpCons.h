// ListpCons.h
// Mara Kim
//
// A recursive cons object 
// a la Lisp

#include <memory>
#include <string>
#include <sstream>

struct ListpElem {
    std::string name;
    double value;
    bool null;

    ListpElem():
    name(),value(0),null(true) {}
    ListpElem(double value):
    name(),value(value),null(false) {}
    ListpElem(std::string name):
    name(name),value(0),null(true) {}
    ListpElem(std::string name,double value):
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

template <class T>
struct ListpCons {
public:
    typedef std::unique_ptr<ListpCons<T> > ptr;
    typedef T Atom;

    ListpCons();
    ListpCons(ListpCons<T>::ptr car, ListpCons<T>::ptr cdr);
    ListpCons(const Atom& atom);
    ptr copy() const;
    virtual bool isAtom() const;
    virtual Atom atom() const;
    void insert(ListpCons<T>::ptr list);
    void push_back(ListpCons<T>::ptr list);
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
    ListpCons<T>::ptr _car, _cdr;
};

template <class T>
class ListpAtom: public ListpCons<T> {
public:
    ListpAtom();
    ListpAtom(typename ListpCons<T>::Atom atom);
    typename ListpCons<T>::ptr copy() const;
    bool isAtom() const;
    typename ListpCons<T>::Atom atom() const;
    std::string print() const;
private:
    typename ListpCons<T>::Atom _atom;
};

