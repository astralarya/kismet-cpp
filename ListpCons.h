// ListpCons.h
// Mara Kim
//
// A recursive cons object 
// a la Lisp

#include <memory>
#include <string>
#include <sstream>
#include <ostream>


template <class T>
struct ListpCons {
public:
    typedef std::unique_ptr<ListpCons<T> > ptr;
    typedef T Atom;
    typedef std::unique_ptr<Atom> AtomPtr;

    ListpCons():
    _car(), _cdr(), _atom() {}

    ListpCons(ptr car, ptr cdr):
    _car(std::move(car)), _cdr(std::move(cdr)), _atom() {}

    ListpCons(ptr car, ptr cdr, AtomPtr atom):
    _car(std::move(car)), _cdr(std::move(cdr)), _atom(std::move(atom)) {}

    ListpCons(const Atom& atom):
    _car(), _cdr(), _atom(new Atom(atom)) {}

    ptr copy() const {
        return ptr(new ListpCons(_car?_car->copy():nullptr,
                                 _cdr?_cdr->copy():nullptr,
                                 _atom?AtomPtr(new Atom(*_atom)):nullptr));
    }

    friend std::ostream& operator<<(std::ostream& out, const ListpCons& cons) {
        if(cons._atom) {
            out << *cons._atom;
            return out;
        } else {
            if(cons._car) {
                if(!cons._car->isAtom())
                    out << '{';
                out << *cons._car;
                if(!cons._car->isAtom())
                    out << '}';
            } else
                out << "NIL";
            if(cons._cdr)
                out << ',' << *cons._cdr;
            return out;
        }
    }

    std::string print(std::string delim = ",", std::string openbr = "{", std::string closebr = "}") const {
        std::stringstream ss;
        if(_atom) {
            ss << *_atom;
            return ss.str();
        } else {
            if(_car) {
                if(!_car->isAtom())
                    ss << openbr;
                ss << _car->print(delim,openbr,closebr);
                if(!_car->isAtom())
                    ss << closebr;
            } else
                ss << "NIL";
            if(_cdr)
                ss << delim << _cdr->print(delim,openbr,closebr);
        }
        return ss.str();
    }

    size_t size() const {
        if(_cdr)
            return 1 + _cdr->size();
        else
            return 1;
    }

    bool isAtom() const {
        if(_atom)
            return true;
        else
            return false;
    }

    const Atom& atom() const {
        return *_atom;
    }

    void insert(ptr list) {
        _cdr = ptr(new ListpCons(std::move(list),std::move(_cdr)));
    }

    void push_back(ptr list) {
        if(!_cdr) {
            _cdr = ptr(new ListpCons(std::move(list),std::move(_cdr)));
        } else
            _cdr->push_back(std::move(list));
    }

    void push_back(Atom atom) {
        push_back(ListpCons::ptr(new ListpCons(atom)));
    }

    // apply a scalar transformation to each atom
    // Func should take a const ListpCons::Atom& and return an ListpCons::Atom
    template<typename Func> void transform(const Func &func) {
        if(_car) {
            if(_car->isAtom())
               _car = std::move(ptr(new ListpCons(func(_car->atom()))));
            else
               _car->transform(func);
        } if(_cdr)
            _cdr->transform(func);
    }

    // map each atom against a list
    // Func should take an const ListpCons::Atom& and return a ListpCons::ptr
    template<typename Func> void map(const Func &func) {
        if(_car) {
            if(_car->isAtom())
               _car = func(_car->atom());
            else
               _car->map(func);
        } if(_cdr)
            _cdr->map(func);
    }

private:
    ptr _car, _cdr;
    AtomPtr _atom;
};

