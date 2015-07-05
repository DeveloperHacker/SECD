#ifndef NIL_H
#define NIL_H

#include <elem.h>

class Nil : public Elem
{
public:
    Nil() = default;
    ~Nil() = default;

    virtual Elem* clone() const;
    virtual bool compare(Elem*) const;
    virtual std::shared_ptr<Elem> get_ptr() const;
    virtual void print(std::ostream &) const;
};

#endif // NIL_H
