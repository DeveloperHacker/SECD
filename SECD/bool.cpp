#include "bool.h"


Bool::Bool(const Bool &elem)
{
    this->value = elem.value;
}

Bool::Bool(bool_t value)
{
    this->value = value;
}


const Bool & Bool::operator =(const Bool &elem)
{
    this->value = elem.value;

    return *this;
}

const Bool & Bool::operator =(bool_t value)
{
    this->value = value;
    return *this;
}

Elem * Bool::clone() const
{
    return new Bool(*this);
}

bool Bool::compare(Elem* orig) const
{
    auto elem = dynamic_cast<Bool*>(orig);

    if (elem != nullptr && elem->get_value() == this->value)
        return true;
    return false;
}

std::shared_ptr<Elem> Bool::get_ptr() const
{
    std::shared_ptr<Elem> temp(new Bool(*this));
    return temp;
}

void Bool::print(std::ostream &out) const
{
    out << (value ? 'T' : 'F');
}


bool_t Bool::get_value() const
{
    return value;
}
