#ifndef CLOSURE_H
#define CLOSURE_H

#include <elem.h>

class Closure : public Elem
{
private:
    std::shared_ptr<Elem> body;
    std::shared_ptr<Elem> enviroment;

public:
    Closure() = default;
    Closure(const Elem & body, const Elem & enviroment);
    Closure(const Closure &);
    ~Closure() = default;

    const Closure & operator =(const Closure &);

    virtual Elem* clone() const;
    virtual bool compare(Elem*) const;
    virtual std::shared_ptr<Elem> get_ptr() const;
    virtual void print(std::ostream &) const;

    Elem & get_enviroment() const;
    Elem & get_body() const;
};

#endif // CLOSURE_H
