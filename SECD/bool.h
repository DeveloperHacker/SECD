#ifndef BOOL_H
#define BOOL_H

#include <elem.h>

typedef bool bool_t;
class Bool : public Elem
{
private:
    bool_t value;

public:
    Bool() = default;
    Bool(const Bool &);
    Bool(bool_t elem);
    ~Bool() = default;

    const Bool & operator = (const Bool &);
    const Bool & operator = (bool_t elem);

    virtual Elem* clone() const;
    virtual bool compare(Elem*) const;
    virtual std::shared_ptr<Elem> get_ptr() const;
    virtual void print(std::ostream &) const;

    bool_t get_value() const;
};

#endif // BOOL_H
