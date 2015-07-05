#ifndef INTEGER_H
#define INTEGER_H

#include <elem.h>

typedef int64_t integer_t;
class Integer : public Elem
{
private:
    integer_t value;

public:
    Integer() = default;
    Integer(const Integer &);
    Integer(integer_t);
    ~Integer() = default;

    const Integer & operator = (const Integer &);
    const Integer & operator = (integer_t);

    virtual Elem* clone() const;
    virtual bool compare(Elem*) const;
    virtual std::shared_ptr<Elem> get_ptr() const;
    virtual void print(std::ostream &) const;

    integer_t get_value() const;
};

#endif // INTEGER_H
