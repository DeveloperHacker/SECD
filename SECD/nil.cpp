#include <nil.h>


Elem* Nil::clone() const
{
    return new Nil(*this);
}

bool Nil::compare(Elem* orig) const
{
    auto elem = dynamic_cast<Nil*>(orig);

    if (elem != nullptr)
        return true;
    return false;
}

std::shared_ptr<Elem> Nil::get_ptr() const
{
    std::shared_ptr<Elem> temp(new Nil(*this));
    return temp;
}

void Nil::print(std::ostream &out) const
{
    out << "Nil";
}
