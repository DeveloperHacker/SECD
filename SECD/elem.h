#ifndef ELEM_H
#define ELEM_H

#include <iostream>
#include <exception.h>
#include <memory>

class Elem
{
public:
    Elem() = default;
    virtual ~Elem() = default;
    virtual Elem* clone() const = 0;
    virtual bool compare(Elem*) const = 0;
    virtual std::shared_ptr<Elem> get_ptr() const = 0;
    virtual void print(std::ostream &) const = 0;

    friend std::ostream & operator << (std::ostream &, const Elem &);
    friend bool operator ==(Elem &, Elem &);
};

#endif // ELEM_H
