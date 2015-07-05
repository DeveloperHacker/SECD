#include "integer.h"


Integer::Integer(const Integer &elem)
{
    this->value = elem.value;
}

Integer::Integer(integer_t value)
{
    this->value = value;
}


const Integer& Integer::operator = (const Integer &elem)
{
    this->value = elem.value;

    return *this;
}

const Integer& Integer::operator = (integer_t value)
{
    this->value = value;

    return *this;
}


Elem* Integer::clone() const
{
    return new Integer(*this);
}

bool Integer::compare(Elem* orig) const
{
    auto elem = dynamic_cast<Integer*>(orig);

    if (elem != nullptr && elem->get_value() == this->value)
        return true;
    return false;
}

std::shared_ptr<Elem> Integer::get_ptr() const
{
    std::shared_ptr<Elem> temp(new Integer(*this));
    return temp;
}

void Integer::print(std::ostream &out) const
{
    out << value;
}


integer_t Integer::get_value() const
{
    return value;
}
