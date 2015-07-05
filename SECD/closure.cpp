#include "closure.h"

Closure::Closure(const Elem &body, const Elem &enviroment)
{
    this->body = body.get_ptr();
    this->enviroment = enviroment.clone()->get_ptr();
}

Closure::Closure(const Closure &elem)
{
    this->body = (*(elem.body)).get_ptr();
    this->enviroment = (*(elem.enviroment)).get_ptr();
}


const Closure& Closure::operator =(const Closure& elem)
{
    if (this != &elem)
    {
        this->body = (*(elem.body)).get_ptr();
        this->enviroment = (*(elem.enviroment)).get_ptr();
    }

    return *this;
}


Elem* Closure::clone() const
{
    return new Closure(*this);
}

bool Closure::compare(Elem* elem) const
{
    auto func = dynamic_cast<Closure*>(elem);

    if(func == nullptr)
        return false;
    else
        return this->body == func->body;
}

std::shared_ptr<Elem> Closure::get_ptr() const
{
    std::shared_ptr<Closure> ptr(new Closure(*this));

    return ptr;
}

void Closure::print(std::ostream &out) const
{
    out << "{ ";
    body->print(out);
    out << " , ";
    enviroment->print(out);
    out << " }";
}


Elem& Closure::get_enviroment() const
{
    return *(this->enviroment);
}

Elem &Closure::get_body() const
{
    return *(this->body);
}
